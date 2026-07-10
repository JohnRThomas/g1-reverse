#include "g1_app_symbols.h"
/* named: gatt_notify_send */
/* Reconstructed gatt_notify_send @ 0x8199a  (parity: 300/300 trials, PROVEN) */

extern int FUN_00057394(void);
extern int FUN_000573f4(int a, int b, int c);
extern short *net_buf_simple_add(int a, int b);
extern void att_send_and_schedule_tx(int a, int b, int c, int d, int e);

unsigned int gatt_notify_send(int param_1, int param_2, int param_3, int param_4)
{
    unsigned int uVar1;
    int iVar2;
    short *puVar3;

    uVar1 = FUN_00057394();
    *(char *)(param_1 + 0xb8) = (char)uVar1;
    iVar2 = FUN_000573f4(0x14, uVar1, 10);
    if (iVar2 == 0) {
        uVar1 = 0xfffffff4;
    } else {
        puVar3 = net_buf_simple_add(iVar2 + 0xc, 10);
        *puVar3 = *(short *)(param_1 + 0xb6);
        puVar3[1] = *(short *)(param_1 + 0x14);
        puVar3[2] = *(short *)(param_1 + 0x16);
        puVar3[3] = *(short *)(param_1 + 0x18);
        puVar3[4] = (short)*(int *)(param_1 + 0x1c);
        att_send_and_schedule_tx(param_1, iVar2, FLASH_OFF_140000 /*=0x140000*/, 0, param_4);
        uVar1 = 0;
    }
    return uVar1;
}

