.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel func_8005402C
/* 4482C 8005402C */ .word 0x15097350
/* 44830 80054030 */ .word 0x00409F9C # invalid instruction
.size func_8005402C, . - func_8005402C
