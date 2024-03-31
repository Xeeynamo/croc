# Croc: Legend of Gobbos decompilation

Creates a full decompilation in C that compiles the same identical binary used the commercial video game Croc: Legend of Gobbos for PlayStation 1.

This decompilation is based on the European demo SLED-00038. This was decided as it is the only known build that contains symbols. This would theorically allow a much faster decompilation. Once the decompilation is complete, the plan is to migrate the existing symbols to the retail build SLUS-00530.

## Progress

| Version      | File name  | Progress
|--------------|------------|----------
| `SLED-00038` | `CROC.EXE` | ![progress](https://img.shields.io/endpoint?url=https://raw.githubusercontent.com/Xeeynamo/croc/gh-report/assets/progress-sled00038-croc.json)
| `SLED-00038` | `DEMOFMV`  | N/A 

## How to setup the project (assuming Ubuntu 20.04/Debian 11 or Windows with WSL)

 1. Inside the folder of your choice `git clone https://github.com/Xeeynamo/croc.git`
 1. Run `sudo apt-get install -y $(cat tools/requirements-debian.txt)`
 1. Run `make update-dependencies`
 1. Copy the content of the disk inside `disks/{game_version}`

## How to build

 1. Run `make extract` to generate the assembly files in the `asm/` directory
 1. Run `make all` to compile the binaries in the `build/` directory

In case there are any changes in the `config/` folder, you might need to run `make clean` to reset the extraction.

Some non-matching functions are present in the source preprocessed by the macro `NON_MATCHING`. You can still compile the game binaries by running `CPP_FLAGS=-DNON_MATCHING make`. In theory they might be logically equivalent in-game, but I cannot promise that. Few of them could match by tuning or changing the compiler.

## How to decompile

1. Run `make clean extract all expected` at least once
1. Look for one of those function which hasn't successfully decompiled yet (eg. `INCLUDE_ASM("asm/croc/nonmatchings/3038", BackGroundTextureLoad);`)
1. Run `FUNC=BackGroundTextureLoad make decompile` to dump the decompiled code on the console
1. Replace the `INCLUDE_ASM(...);` you targeted with the console output content
1. and invoke `python3 ./tools/asm-differ/diff.py -mwo BackGroundTextureLoad`

You will probably have some differences from your compiled code to the original; keep refactoring the code and move variables around until you have a 100% match.

There are a few tricks to make the process more streamlined:

1. Use [decomp.me](https://decomp.me/) with the PSY-Q 4.0 compiler.
1. The “context” section of decomp.me, is provided by the previous command `make decompile` as mentioned in the how to decompile.
1. Use [decomp-permuter](https://github.com/simonlindholm/decomp-permuter) to solve some mismatches
1. Use [this](https://github.com/mkst/sssv/wiki/Jump-Tables) and [this](https://github.com/pmret/papermario/wiki/GCC-2.8.1-Tips-and-Tricks) guide to understand how some compiler patterns work
1. Use the `#ifndef NON_MATCHING` if your code is logically equivalent but you cannot yet fully match it

## Troubleshooting

### Not getting an "OK" on Ubuntu 22.04

Debian>=12 and Ubuntu>=22.04 uses `binutils-mipsel-linux-gnu`>=2.38 which, for some unknown reasons, it generates broken binaries. You need to downgrade to 2.34 or 2.35 with the following:

```shell
curl -L -o binutils-mipsel-linux-gnu_2.35.2-2cross2_amd64.deb http://ftp.de.debian.org/debian/pool/main/b/binutils-mipsen/binutils-mipsel-linux-gnu_2.35.2-2cross2_amd64.deb
dpkg -i binutils-mipsel-linux-gnu_2.35.2-2cross2_amd64.deb
rm binutils-mipsel-linux-gnu_2.35.2-2cross2_amd64.deb
```
