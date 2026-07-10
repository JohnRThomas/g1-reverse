#include "g1_net_symbols.h"
/* net-core FUN_01034fa8 @ 0x1034fa8  (parity 300 trials PROVEN) */

extern int FUN_01034f24(void);
extern int FUN_01039bbe(int, int, int);
extern void FUN_01039bb0(int, int) __attribute__((noreturn));

int FUN_01034fa8(unsigned int *param_1, int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned char uVar1 = *((unsigned char*)param_1 + 4);
    int iVar5 = uVar1 * 0xc;
    volatile unsigned char *base = (volatile unsigned char*)((uintptr_t)&g_net_gpiote_evt_handler_table) /*=0x21004af8*/;
    int iVar4;
    if (*(volatile unsigned char*)(base + iVar5 + 8) == 0) {
        *(volatile unsigned int*)(base + iVar5) = param_3;
        if (param_2 != 0) {
            *(volatile unsigned int*)(base + iVar5 + 4) = *(unsigned int*)(param_2 + 8);
            unsigned int uVar6 = *param_1;
            unsigned int uVar3c = REG_4100c000 /*=0x4100c000*/;
            int matched = (uVar6 == uVar3c) || (uVar6 == uVar3c + 0xc000) || (uVar6 == uVar3c + 0xd000);
            if (!matched || (*((unsigned char*)param_2 + 5) > 3)) {
                FUN_01039bbe("acking error (context area might be not valid)" /*=0x103d2a7*/, ((uintptr_t)&rodata_103e73b) /*=0x103e73b*/, 0x8e);
                FUN_01039bb0(((uintptr_t)&rodata_103e73b) /*=0x103e73b*/, 0x8e);
            }
            iVar4 = FUN_01034f24();
        } else {
            iVar4 = 0x0bad0000;
        }
        *(volatile unsigned char*)(base + iVar5 + 8) = (iVar4 == (int)0x0bad0000) ? 1 : 0;
    } else {
        iVar4 = 0x0bad0005;
    }
    return iVar4;
}

