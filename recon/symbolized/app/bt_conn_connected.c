#include "g1_app_symbols.h"
/* named: bt_conn_connected */
/* Reconstructed bt_conn_connected @ 0x8144a  (parity: 300/300 trials, PROVEN) */

extern void bt_l2cap_connected(void);
extern void FUN_00055fb4(unsigned int a);

void bt_conn_connected(unsigned int param_1)
{
    bt_l2cap_connected();
    FUN_00055fb4(param_1);
}

