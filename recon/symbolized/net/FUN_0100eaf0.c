#include "g1_net_symbols.h"
/* net-core FUN_0100eaf0 @ 0x100eaf0  (parity 6 trials PROVEN) */
#include <stdint.h>

extern void FUN_01008d00(unsigned int a, unsigned int b);
extern unsigned int FUN_0100a118(void);
extern int FUN_0100e5ec(int a);
extern void FUN_01025998(int a, int b, unsigned short c);
extern int FUN_01026c94(unsigned int a, int b);
extern int FUN_01027044(void);
extern unsigned int FUN_0102709e(unsigned int a, int b, void *c);
extern int FUN_010270e8(unsigned int a);

#define DAT_ebb4 ((uintptr_t)&g_net_ble_conn_create_ctx) /*=0x21000eac*/

void FUN_0100eaf0(unsigned short param_1, int *param_2)
{
    unsigned int uVar1;
    int iVar2;
    unsigned int uVar3;
    int local_14[2];
    unsigned char *p2;

    if (param_2 == 0) {
        for (;;) {
            FUN_01008d00(0x10, 0x110);
        }
    }
    p2 = (unsigned char *)param_2;
    *(volatile unsigned short *)(p2 + 4) = param_1;
    *(volatile unsigned char *)(p2 + 9) = 0;
    uVar1 = FUN_0100a118();
    iVar2 = FUN_01027044();
    if (iVar2 == 0) {
        FUN_01008d00(0x10, 0x119);
        for (;;) {
            FUN_01008d00(0x10, 0x110);
        }
    }
    uVar3 = FUN_0102709e(uVar1, iVar2, local_14);
    *(volatile unsigned short *)(p2 + 6) = (unsigned short)uVar3;
    if (uVar3 == 0) {
        FUN_01008d00(0x10, 0x11e);
        FUN_01008d00(0x10, 0x119);
        for (;;) {
            FUN_01008d00(0x10, 0x110);
        }
    }
    if (uVar3 >= 0xfc) {
        FUN_01008d00(0x10, 0x120);
        FUN_01008d00(0x10, 0x11e);
        FUN_01008d00(0x10, 0x119);
        for (;;) {
            FUN_01008d00(0x10, 0x110);
        }
    }

    iVar2 = FUN_0100e5ec(local_14[0]);
    if (iVar2 != 1 && iVar2 != 2) {
        FUN_01008d00(0x10, 0x130);
        FUN_01008d00(0x10, 0x137);
        FUN_01008d00(0x10, 0x141);
        FUN_01008d00(0x10, 0x13c);
        FUN_01008d00(0x10, 0x120);
        FUN_01008d00(0x10, 0x11e);
        FUN_01008d00(0x10, 0x119);
        for (;;) {
            FUN_01008d00(0x10, 0x110);
        }
    }
    *(volatile unsigned char *)(p2 + 8) = (unsigned char)iVar2;
    if (*param_2 == 0) {
        FUN_01008d00(0x10, 0x137);
        FUN_01008d00(0x10, 0x141);
        FUN_01008d00(0x10, 0x13c);
        FUN_01008d00(0x10, 0x120);
        FUN_01008d00(0x10, 0x11e);
        FUN_01008d00(0x10, 0x119);
        for (;;) {
            FUN_01008d00(0x10, 0x110);
        }
    }
    FUN_01025998(*param_2, local_14[0] + 3, *(volatile unsigned short *)(p2 + 6));
    iVar2 = FUN_010270e8(uVar1);
    if (iVar2 != 0) {
        iVar2 = FUN_01026c94(uVar1, 0);
        if (iVar2 != 0) {
            if (*(volatile char *)(DAT_ebb4 + 0x17) != 0) {
                *(volatile short *)(DAT_ebb4 + 0x18) = *(volatile short *)(DAT_ebb4 + 0x18) - 1;
            }
            return;
        }
        FUN_01008d00(0x10, 0x141);
        FUN_01008d00(0x10, 0x13c);
        FUN_01008d00(0x10, 0x120);
        FUN_01008d00(0x10, 0x11e);
        FUN_01008d00(0x10, 0x119);
        for (;;) {
            FUN_01008d00(0x10, 0x110);
        }
    }
    FUN_01008d00(0x10, 0x13c);
    FUN_01008d00(0x10, 0x120);
    FUN_01008d00(0x10, 0x11e);
    FUN_01008d00(0x10, 0x119);
    for (;;) {
        FUN_01008d00(0x10, 0x110);
    }
}

