.SECONDEXPANSION:
.SECONDARY:

# Binaries
BUILD           := sled00038
BOOT            := boot
CROC            := croc

# Compilers
CROSS           := mipsel-linux-gnu-
AS              := $(CROSS)as
CC              := ./bin/cc1-27
LD              := $(CROSS)ld
CPP				:= $(CROSS)cpp
OBJCOPY         := $(CROSS)objcopy
AS_FLAGS        += -Iinclude -march=r3000 -mtune=r3000 -no-pad-sections -O1
CC_FLAGS        += -mips1 -mcpu=3000 -quiet -G0 -Wall -fno-builtin -mno-abicalls -funsigned-char -O1
CPP_FLAGS       += -Iinclude -Iinclude/psyq -undef -Wall -lang-c -fno-builtin -gstabs
CPP_FLAGS       += -Dmips -D__GNUC__=2 -D__OPTIMIZE__ -D__mips__ -D__mips -Dpsx -D__psx__ -D__psx -D_PSYQ -D__EXTENSIONS__ -D_MIPSEL -D_LANGUAGE_C -DLANGUAGE_C

# Directories
ASM_DIR         := asm
SRC_DIR         := src
INCLUDE_DIR     := include
BUILD_DIR       := build
CONFIG_DIR      := config
TOOLS_DIR       := tools

# Files
CROC_ASM_DIRS   := $(ASM_DIR)/$(CROC) $(ASM_DIR)/$(CROC)/psxsdk $(ASM_DIR)/$(CROC)/data
CROC_SRC_DIRS   := $(SRC_DIR)/$(CROC) $(SRC_DIR)/$(CROC)/psxsdk
CROC_S_FILES    := $(foreach dir,$(CROC_ASM_DIRS),$(wildcard $(dir)/*.s)) \
					$(foreach dir,$(CROC_ASM_DIRS),$(wildcard $(dir)/**/*.s))
CROC_C_FILES    := $(foreach dir,$(CROC_SRC_DIRS),$(wildcard $(dir)/*.c)) \
					$(foreach dir,$(CROC_SRC_DIRS),$(wildcard $(dir)/**/*.c))
CROC_O_FILES    := $(foreach file,$(CROC_S_FILES),$(BUILD_DIR)/$(file).o) \
					$(foreach file,$(CROC_C_FILES),$(BUILD_DIR)/$(file).o)
CROC_TARGET     := $(BUILD_DIR)/$(CROC)

# Tooling
PYTHON          := python3
SPLAT_DIR       := $(TOOLS_DIR)/splat
SPLAT_APP       := $(SPLAT_DIR)/split.py
SPLAT           := $(PYTHON) $(SPLAT_APP)
ASMDIFFER_DIR   := $(TOOLS_DIR)/asm-differ
ASMDIFFER_APP   := $(ASMDIFFER_DIR)/diff.py
M2CTX_APP       := $(TOOLS_DIR)/m2ctx.py
M2CTX           := $(PYTHON) $(M2CTX_APP)
M2C_DIR         := $(TOOLS_DIR)/m2c
M2C_APP         := $(M2C_DIR)/m2c.py
M2C             := $(PYTHON) $(M2C_APP)
M2C_ARGS		:= -P 4
MASPSX_DIR      := $(TOOLS_DIR)/maspsx
MASPSX_APP      := $(MASPSX_DIR)/maspsx.py
MASPSX          := $(PYTHON) $(MASPSX_APP) --expand-div --aspsx-version=2.56

define list_src_files
	$(foreach dir,$(ASM_DIR)/$(1),$(wildcard $(dir)/**.s))
	$(foreach dir,$(ASM_DIR)/$(1)/data,$(wildcard $(dir)/**.s))
	$(foreach dir,$(ASM_DIR)/$(1)/psxsdk,$(wildcard $(dir)/**.s))
	$(foreach dir,$(SRC_DIR)/$(1),$(wildcard $(dir)/**.c))
	$(foreach dir,$(SRC_DIR)/$(1)/psxsdk,$(wildcard $(dir)/**.c))
endef

define list_o_files
	$(foreach file,$(call list_src_files,$(1)),$(BUILD_DIR)/$(file).o)
endef

define link
	$(LD) -o $(2) \
		-Map $(BUILD_DIR)/$(1).map \
		-T $(1).ld \
		-T $(CONFIG_DIR)/undefined_syms_auto.$(BUILD).$(1).txt \
		-T $(CONFIG_DIR)/undefined_funcs_auto.$(BUILD).$(1).txt \
		--no-check-sections \
		-nostdlib \
		-s
endef

all: build check
build: croc
clean:
	git clean -fdx asm/
	git clean -fdx $(BUILD_DIR)
	git clean -fdx config/
format:
	clang-format -i $$(find $(SRC_DIR)/ -type f -name "*.c")
	clang-format -i $$(find $(SRC_DIR)/ -type f -name "*.h")
	clang-format -i $$(find $(INCLUDE_DIR)/ -type f -name "*.h")
	black tools/*.py
check:
	sha1sum --check config/check.sled00038.sha
expected: check
	rm -rf expected/build
	cp -r build expected/

croc.elf: $(CROC_O_FILES)
	$(LD) -o $@ \
	-Map $(CROC_TARGET).map \
	-T $(CROC).ld \
	-T $(CONFIG_DIR)/undefined_syms_auto.$(CROC).txt \
	--no-check-sections \
	-nostdlib \
	-s

croc: croc_dirs $(BUILD_DIR)/CROC.EXE
$(BUILD_DIR)/CROC.EXE: $(BUILD_DIR)/$(CROC).elf
	$(OBJCOPY) -O binary $< $@
$(BUILD_DIR)/$(CROC).elf: $(call list_o_files,croc)
	$(call link,croc,$@)

%_dirs:
	$(foreach dir,$(ASM_DIR)/$* $(ASM_DIR)/$*/data $(SRC_DIR)/$*,$(shell mkdir -p $(BUILD_DIR)/$(dir)))

$(BUILD_DIR)/%.elf: $$(call list_o_files,$$*)
	$(call link,$*,$@)

extract: extract_croc
extract_croc: require-tools
	$(SPLAT) $(CONFIG_DIR)/splat.sled00038.croc.yml
$(CONFIG_DIR)/symbols.%.txt:

decompile: $(M2C_APP)
	$(M2CTX) src/croc/3038.c
	$(M2C_APP) $(M2C_ARGS) --target mipsel-gcc-c --context ctx.c asm/croc/nonmatchings/3038/$(FUNC).s

require-tools: $(SPLAT_APP) $(ASMDIFFER_APP)
update-dependencies: require-tools $(M2CTX_APP) $(M2C_APP)
	pip3 install -r $(TOOLS_DIR)/requirements-python.txt

$(SPLAT_APP):
	git submodule init $(SPLAT_DIR)
	git submodule update $(SPLAT_DIR)
	pip3 install -r $(SPLAT_DIR)/requirements.txt
$(ASMDIFFER_APP):
	git submodule init $(ASMDIFFER_DIR)
	git submodule update $(ASMDIFFER_DIR)
$(M2CTX_APP):
	curl -o $@ https://raw.githubusercontent.com/ethteck/m2ctx/main/m2ctx.py
$(M2C_APP):
	git submodule init $(M2C_DIR)
	git submodule update $(M2C_DIR)
	python3 -m pip install --upgrade pycparser
$(MASPSX_APP):
	git submodule init $(MASPSX_DIR)
	git submodule update $(MASPSX_DIR)

$(BUILD_DIR)/%.s.o: %.s
	$(AS) $(AS_FLAGS) -o $@ $<
$(BUILD_DIR)/%.bin.o: %.bin
	$(LD) -r -b binary -o -Map %.map $@ $<
$(BUILD_DIR)/%.c.o: %.c $(MASPSX_APP)
	$(CPP) $(CPP_FLAGS) $< | $(CC) $(CC_FLAGS) | $(MASPSX) | $(AS) $(AS_FLAGS) -o $@

SHELL = /bin/bash -e -o pipefail

.PHONY: all, clean, format, check, expected
.PHONY: croc, boot
.PHONY: extract_croc, extract_boot
.PHONY: require-tools, update-dependencies
