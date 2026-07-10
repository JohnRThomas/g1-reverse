#include "g1_app_symbols.h"
/* named: FUN_0002ead8 */
/* Reconstructed FUN_0002ead8 @ 0x2ead8  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(int);
extern int dev_ctrl_read1(int,int,int,void*,int);

unsigned int FUN_0002ead8(int param_1, unsigned int param_2)
{
    unsigned char byte7 = 0;
    int base = *(volatile int*)(((uintptr_t)&tbl_87c80) /*=0x87ce0*/ + 4);
    int arg0 = *(volatile int*)(base + 0x1c);
    int iVar1 = dev_ctrl_read1(arg0, 3, 0x34, &byte7, param_1);
    unsigned int uVar2;
    if (iVar1 < 0) {
        DEBUG_PRINT("Could not get charger status\n" /*=0xa3e62*/);
        uVar2 = 0xffffffff;
    } else {
        unsigned int combined = (byte7 >> 3) | (byte7 >> 2);
        if (combined & 1) {
            uVar2 = 0;
        } else {
            uVar2 = (~(unsigned int)(byte7 >> 4)) & 1;
        }
    }
    return uVar2;
}

