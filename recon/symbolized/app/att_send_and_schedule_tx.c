#include "g1_app_symbols.h"
/* named: att_send_and_schedule_tx */
/* Reconstructed att_send_and_schedule_tx @ 0x81962  (parity: 300/300 trials, PROVEN) */

extern unsigned long long bt_conn_create_pdu(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e, unsigned int f, unsigned int g);
extern void net_buf_unref(unsigned int a);
extern void FUN_0007350c(unsigned int *a, unsigned int b, unsigned int c, unsigned int d);

void att_send_and_schedule_tx(unsigned int *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned long long uVar1;
    uVar1 = bt_conn_create_pdu(*param_1, 5, param_2, 0, 0, param_2, param_3);
    if ((int)uVar1 != 0) {
        net_buf_unref(param_2);
        return;
    }
    FUN_0007350c(param_1 + 0x30, (unsigned int)(uVar1 >> 32), param_3, param_4);
}

