#include "g1_net_symbols.h"
/* net-core FUN_0101ffd4 @ 0x101ffd4  (parity 300 trials PROVEN) */

extern void FUN_01008d00(unsigned int, unsigned int, unsigned int, unsigned int) __attribute__((noreturn));
extern void FUN_0102a21e(void);

void FUN_0101ffd4(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    volatile unsigned char *p38 = (volatile unsigned char*)((uintptr_t)&g_net_radio_pending_reset_flag) /*=0x210014dc*/;
    volatile unsigned char *e000 = (volatile unsigned char*)REG_4100e000 /*=0x4100e000*/;
    volatile unsigned char *ed00 = (volatile unsigned char*)0xe000ed00;
    volatile unsigned char *e100 = (volatile unsigned char*)0xe000e100;

    if (*p38 != 0) {
        if (*(volatile unsigned int*)(e000+0x104) == 0) {
            *(volatile unsigned int*)(e000+0x304) = 2;
            unsigned int r7 = *(volatile unsigned int*)(ed00+0x10) & 0x10;
            *(volatile unsigned int*)(ed00+0x10) = *(volatile unsigned int*)(ed00+0x10) | 0x10;
            while (*(volatile unsigned int*)(e000+0x104) == 0) {
                *(volatile unsigned int*)(e100+0x180) = 0x4000;
                FUN_0102a21e();
            }
            if (r7 == 0) {
                *(volatile unsigned int*)(ed00+0x10) = *(volatile unsigned int*)(ed00+0x10) & 0xffffffef;
            }
            *(volatile unsigned int*)(e000+0x308) = 2;
        }
        return;
    }
    FUN_01008d00(0x3c, 0x280, param_3, param_4);
}

