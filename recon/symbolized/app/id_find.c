#include "g1_app_symbols.h"
/* named: id_find */
/* globals referenced:
//   0x20002000  g_ble_dev_state              
*/
/* Reconstructed id_find @ 0x54ce8  (parity: 300/300 trials, PROVEN) */

extern int bt_addr_le_eq(int,int,int,int,int);
unsigned int id_find(int param_1, int param_2, int param_3, int param_4)
{
    volatile char *base = (volatile char*)((uintptr_t)&g_ble_dev_state) /*=0x20002000*/;
    unsigned char bVar1 = *(volatile unsigned char*)(base + 7);
    unsigned int uVar2 = 0;
    volatile char *iVar5 = base;
    int iVar3;
    unsigned int uVar4;
    do {
        uVar4 = uVar2;
        if (bVar1 <= (uVar4 & 0xff)) {
            return 0xfffffffe;
        }
        iVar3 = bt_addr_le_eq(param_1, (int)iVar5, param_3, uVar4 & 0xff, param_4);
        iVar5 = iVar5 + 7;
        uVar2 = uVar4 + 1;
    } while (iVar3 == 0);
    return uVar4;
}

