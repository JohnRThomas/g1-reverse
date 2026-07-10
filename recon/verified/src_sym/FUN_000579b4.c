/* Reconstructed FUN_000579b4 @ 0x579b4  (parity: 300/300 trials, PROVEN) */

void bt_l2cap_le_lookup_tx_cid(unsigned int param_1)
{
    int *piVar1 = *(volatile int**)0x2000ad2cUL;
    while (piVar1 != (int*)0 && *(volatile unsigned short*)((char*)piVar1 - 8) != param_1) {
        piVar1 = *(volatile int**)piVar1;
    }
}

