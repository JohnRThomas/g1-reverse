#include "g1_net_symbols.h"
/* net-core FUN_01035edc @ 0x1035edc  (parity 300 trials PROVEN) */

typedef unsigned int uint;
extern void FUN_0102ece0(int,int,int,int,unsigned int,unsigned int,unsigned int);
extern int FUN_0102edac(int,int);
extern void FUN_01039bb0(unsigned int,unsigned int);
extern void FUN_01039bbe(unsigned int,unsigned int,unsigned int);

int FUN_01035edc(int param_1, int param_2, int param_3, int param_4b, unsigned int param_5,
                  unsigned int param_6, unsigned int param_7, int param_8, unsigned char param_9)
{
    if (param_8 == 0xf) {
        if (param_4b != ((uintptr_t)&rodata_1036955) /*=0x1036955*/) {
            FUN_01039bbe("acking error (context area might be not valid)" /*=0x103d2a7*/, ((uintptr_t)&rodata_103ea45) /*=0x103ea45*/, 0x21a);
            FUN_01039bb0(((uintptr_t)&rodata_103ea45) /*=0x103ea45*/, 0x21a);
            __builtin_unreachable();
        }
    } else if ((unsigned int)(param_8 + 0x10) > 0x1e) {
        FUN_01039bbe("acking error (context area might be not valid)" /*=0x103d2a7*/, ((uintptr_t)&rodata_103ea45) /*=0x103ea45*/, 0x21a);
        FUN_01039bb0(((uintptr_t)&rodata_103ea45) /*=0x103ea45*/, 0x21a);
        __builtin_unreachable();
    }
    *(volatile int*)(param_1 + 0x58) = param_1 + 0x58;
    *(volatile int*)(param_1 + 0x5c) = param_1 + 0x58;
    *(volatile unsigned char*)(param_1 + 0xc) = param_9;
    unsigned int uVar2 = (param_3 + 7) & 0xfffffff8;
    int iVar3 = uVar2 + 0x40 + param_2;
    *(volatile unsigned char*)(param_1 + 0xd) = 4;
    *(volatile signed char*)(param_1 + 0xe) = (signed char)param_8;
    *(volatile int*)(param_1 + 0x18) = 0;
    *(volatile int*)(param_1 + 0x1c) = 0;
    *(volatile int*)(param_1 + 8) = 0;
    *(volatile unsigned char*)(param_1 + 0xf) = 0;
    int iVar1 = FUN_0102edac(param_1, iVar3);
    *(volatile int*)(param_1 + 0x78) = param_2 + 0x40;
    *(volatile unsigned int*)(param_1 + 0x7c) = uVar2;
    unsigned int uVar2b = (iVar1 + 7) & 0xfffffff8;
    *(volatile unsigned int*)(param_1 + 0x80) = uVar2b;
    int iVar3b = iVar3 - uVar2b;
    FUN_0102ece0(param_1, param_2, iVar3b, param_4b, param_5, param_6, param_7);
    volatile int * const p_1035f94 = (volatile int *)((uintptr_t)&g_zephyr_kernel_readyq) /*=0x21004b28*/; /* DAT_01035f94 */
    *(volatile int*)(param_1 + 0x54) = 0;
    int iVar1b = *(volatile int*)((unsigned char*)p_1035f94 + 8);
    *(volatile int*)(param_1 + 0x74) = 0;
    *(volatile unsigned char*)(param_1 + 0x70) = 0;
    if (iVar1b != 0) {
        iVar1b = *(volatile int*)(iVar1b + 0x84);
    }
    *(volatile int*)(param_1 + 0x84) = iVar1b;
    return iVar3b;
}

