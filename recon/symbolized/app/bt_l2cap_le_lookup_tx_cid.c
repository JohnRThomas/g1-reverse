#include "g1_app_symbols.h"
/* named: bt_l2cap_le_lookup_tx_cid */
/* Reconstructed bt_l2cap_le_lookup_tx_cid @ 0x81aca  (parity: 300/300 trials, PROVEN) */

void bt_l2cap_le_lookup_tx_cid(int param_1, unsigned int param_2)
{
    int *piVar1;
    for (piVar1 = *(int **)(param_1 + 0x54);
         piVar1 != (int *)0 && *(unsigned short *)((char*)piVar1 + 0xc) != (unsigned short)param_2;
         piVar1 = (int *)*piVar1) {
    }
}

