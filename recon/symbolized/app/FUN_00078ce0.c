#include "g1_app_symbols.h"
/* named: FUN_00078ce0 */
/* Reconstructed FUN_00078ce0 @ 0x78ce0  (parity: 300/300 trials, PROVEN) */

extern int libc_fatal_error_and_abort(unsigned a, unsigned b, int c, unsigned d);
extern int Balloc(unsigned a, int b);
extern int clz32(unsigned a);
extern int ctz32_normalize_inplace(void*a);
int FUN_00078ce0(unsigned a0, unsigned a1, unsigned a2){
    unsigned lo, hi;
    __asm__ volatile(".fpu fpv5-sp-d16\n\tvmov %0, %1, d0\n\t.fpu softvfp" : "=r"(lo), "=r"(hi));
    int iVar1 = Balloc(a0, 1);
    if (iVar1 == 0) libc_fatal_error_and_abort("/__w/_temp/workspace/build/.build/HOST-x86_64-w64-mingw32/arm-zephyr-eabi/src/newlib-nano/newlib/libc/stdlib/mprec.c" /*=0xf8cd5*/, 0x30a, 0, "Balloc succeeded" /*=0xf8c42*/);
    unsigned uVar6 = (hi >> 20) & 0x7ff;
    unsigned mant = hi & ((uintptr_t)&rodata_fffff) /*=0xfffff*/;
    if (uVar6 != 0) mant |= FLASH_OFF_100000 /*=0x100000*/;
    unsigned uVar2, iVar4;
    if (lo == 0){
        unsigned tmp = mant;
        int r = ctz32_normalize_inplace(&tmp);
        uVar2 = (unsigned)r + 0x20;
        iVar4 = 1;
        *(volatile unsigned*)(iVar1 + 0x14) = tmp;
        mant = tmp;
    } else {
        unsigned buf[2]; buf[0] = lo; buf[1] = mant;
        int r = ctz32_normalize_inplace(buf);
        uVar2 = (unsigned)r;
        unsigned l1 = buf[0]; unsigned l2 = buf[1];
        if (uVar2 == 0){
            *(volatile unsigned*)(iVar1 + 0x14) = l1;
            mant = l2;
        } else {
            unsigned uVar5 = l2 << ((0x20 - uVar2) & 0xff);
            mant = l2 >> (uVar2 & 0xff);
            *(volatile unsigned*)(iVar1 + 0x14) = uVar5 | l1;
        }
        *(volatile unsigned*)(iVar1 + 0x18) = mant;
        iVar4 = (mant == 0) ? 1 : 2;
    }
    *(volatile int*)(iVar1 + 0x10) = (int)iVar4;
    int iVar3;
    if (uVar6 == 0){
        *(volatile int*)a1 = (int)(uVar2 - 0x432);
        int t = clz32(*(volatile unsigned*)(iVar1 + iVar4*4 + 0x10));
        iVar3 = (int)iVar4 * 0x20 - t;
    } else {
        iVar3 = 0x35 - (int)uVar2;
        *(volatile int*)a1 = (int)((uVar6 - 0x433) + uVar2);
    }
    *(volatile int*)a2 = iVar3;
    return iVar1;
}

