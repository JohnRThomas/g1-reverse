#include "g1_net_symbols.h"
/* net-core FUN_01014a50 @ 0x1014a50  (parity 300 trials PROVEN) */
#include <stdint.h>

extern int FUN_0100e7d0(unsigned int a);
extern int FUN_0100e7d4(unsigned int a);
extern int FUN_0100e7d8(unsigned int a);
extern int FUN_0100e7dc(unsigned int a);
extern int FUN_0100e7e0(unsigned int a);
extern void FUN_0100f198(int a, int b, int c, int d, int e);
extern void FUN_0100f2d0(unsigned short a, void *b, void *c);
extern void FUN_0100f798(int a);
extern unsigned int FUN_0100f834(int a, unsigned int b);

#define DAT_b14 ((uintptr_t)&g_net_link_ctx_a) /*=0x21000f68*/

unsigned int FUN_01014a50(int param_1, unsigned int param_2)
{
    int iVar1;
    int uVar2, uVar3, uVar4, uVar5;

    iVar1 = FUN_0100e7e0(param_2);
    if (iVar1 == 0) {
        return FUN_0100f834(param_1, param_2);
    }

    iVar1 = *(volatile int *)(param_1 + 4);
    uVar2 = FUN_0100e7d8(param_2);
    uVar3 = FUN_0100e7d0(param_2);
    uVar4 = FUN_0100e7dc(param_2);
    uVar5 = FUN_0100e7d4(param_2);
    FUN_0100f198(iVar1 + 0x30, uVar2, uVar3, uVar4, uVar5);

    if ((int)((unsigned int)(*(volatile unsigned short *)(DAT_b14 + 0xc)) << 0x1e) < 0 &&
        *(volatile unsigned char *)(*(volatile int *)(DAT_b14 + 0x10) + 3) == 0x14) {
        iVar1 = *(volatile int *)(param_1 + 4);
        *(volatile unsigned char *)(iVar1 + 100) = 1;
    } else {
        iVar1 = *(volatile int *)(param_1 + 4);
        if (*(volatile unsigned char *)(iVar1 + 0xc5) == 0x1e) {
            *(volatile unsigned char *)(iVar1 + 100) = 1;
        } else if (*(volatile unsigned char *)(iVar1 + 100) != 1 &&
                   *(volatile unsigned char *)(iVar1 + 0x163) == 0 &&
                   *(volatile unsigned char *)(iVar1 + 0x162) == 0) {
            unsigned short *puVar6 = *(volatile unsigned short **)(DAT_b14 + 4);
            *(volatile unsigned int *)(iVar1 + 0xb4) = *(volatile unsigned int *)(iVar1 + 0xb4) | 0x20;
            FUN_0100f2d0(*puVar6, puVar6 + 0x18, puVar6 + 0xf1);
            FUN_0100f798(param_1);
            return 0;
        } else {
            *(volatile unsigned int *)(iVar1 + 0xb4) = *(volatile unsigned int *)(iVar1 + 0xb4) | 0x10;
            FUN_0100f798(param_1);
            return 0;
        }
    }
    *(volatile unsigned int *)(iVar1 + 0xb4) = *(volatile unsigned int *)(iVar1 + 0xb4) | 0x10;
    FUN_0100f798(param_1);
    return 0;
}

