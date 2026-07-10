/* Reconstructed FUN_00082594 @ 0x82594  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern unsigned int bt_l2cap_le_lookup_tx_cid(int a,int b,int c,int d,int e);
unsigned int FUN_00082594(int param_1, int param_2, int param_3, int param_4) {
    unsigned int uVar1 = bt_l2cap_le_lookup_tx_cid(param_1, 4, param_3, param_4, param_4);
    if (uVar1 != 0) {
        int v = *(volatile int*)(uVar1 + 0x118);
        uVar1 = (unsigned int)((v << 0x1a) >> 0x1f);
    }
    return uVar1;
}

