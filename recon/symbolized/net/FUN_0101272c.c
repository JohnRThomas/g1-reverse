#include "g1_net_symbols.h"
/* net-core FUN_0101272c @ 0x101272c  (parity 300 trials PROVEN) */
#include <stdint.h>

extern void FUN_0100ef88(void *a, unsigned int b, int c);
extern void FUN_010140ec(unsigned char *a, int b, ...);
extern int FUN_0101f888(void);
extern void FUN_0101fca8(void);
extern void FUN_010208b0(void);

#define DAT_7f0 ((unsigned long)&g_net_own_addr_info) /*=0x21000f20*/
#define LIT_7f4 ((unsigned long)&rodata_1011add) /*=0x1011add*/

unsigned int FUN_0101272c(unsigned char *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    int iVar3;
    unsigned char cVar4;
    unsigned short uVar5;
    unsigned int uVar2;
    unsigned short uVar1;

    iVar3 = DAT_7f0;
    if (*(volatile char *)(DAT_7f0 + 4) != 1) {
        return 0;
    }
    cVar4 = *(volatile unsigned char *)(DAT_7f0 + 0x12);
    *(volatile unsigned short *)(param_1 + 0x40) = *(volatile unsigned short *)(param_1 + 0x40) + 1;
    if (cVar4 != 0) {
        FUN_010208b0();
        FUN_0101fca8();
        *(volatile unsigned char *)(iVar3 + 0x12) = 0;
    }
    *(volatile unsigned char *)(iVar3 + 4) = 0;

    if (param_1[0x79] != 0) {
        FUN_010140ec(param_1, 1);
        return 0;
    }

    uVar5 = (unsigned short)param_1[0xd];
    if (uVar5 == 0 || *(volatile unsigned short *)(param_1 + 0x40) < uVar5) {
        FUN_010140ec(param_1, 0);
        return 0;
    }

    FUN_010140ec(param_1, 1, *(volatile unsigned short *)(param_1 + 0x40), uVar5, param_4);

    if ((int)((unsigned int)*(volatile unsigned short *)(param_1 + 2) << 0x1f) < 0) {
        uVar1 = **(volatile unsigned short **)(param_1 + 0x1c);
        iVar3 = FUN_0101f888();
        if (iVar3 != 0) {
            return 0;
        }
        cVar4 = param_1[0xd];
        *(volatile unsigned short *)(param_1 + 0xb1) = uVar1;
        param_1[0xb0] = *param_1;
        param_1[0xaf] = 0x43;
        uVar2 = LIT_7f4;
    } else {
        iVar3 = FUN_0101f888();
        if (iVar3 != 0) {
            return 0;
        }
        cVar4 = param_1[0xd];
        param_1[0xb0] = *param_1;
        param_1[0xb1] = 0xff;
        param_1[0xb2] = 0xff;
        param_1[0xaf] = 0x43;
        uVar2 = LIT_7f4;
    }

    if (cVar4 != 0) {
        cVar4 = param_1[0x40];
    }
    param_1[0xb3] = cVar4;
    FUN_0100ef88(param_1 + 0xa6, uVar2, 2);
    return 0;
}
