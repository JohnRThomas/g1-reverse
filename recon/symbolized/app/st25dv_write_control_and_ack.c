#include "g1_app_symbols.h"
/* named: st25dv_write_control_and_ack */
/* globals referenced:
//   0x20007a44  g_st25dv_dev                 
*/
/* Reconstructed st25dv_write_control_and_ack @ 0x24f40  (parity: 300/300 trials, PROVEN) */

extern int FUN_0007c8d0(unsigned int a, unsigned int b, unsigned int c, unsigned int d);
extern int FUN_0007c8e8(unsigned int a, void *b);
extern void FUN_0007c8fa(unsigned int a);

void st25dv_write_control_and_ack(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    volatile unsigned int *puVar1 = (volatile unsigned int*)((uintptr_t)&g_st25dv_dev) /*=0x20007a44*/;
    unsigned char localbuf[8];
    unsigned int val = *puVar1;
    int iVar2 = FUN_0007c8d0(val, param_1 & 0xff, param_3, param_4);
    if (iVar2 == 0) {
        val = *puVar1;
        iVar2 = FUN_0007c8e8(val, localbuf);
        if (iVar2 == 0) {
            unsigned char b = ((param_1 >> 8) & 3) | 0xc;
            localbuf[0] = b;
            val = *puVar1;
            FUN_0007c8fa(val);
        }
    }
}

