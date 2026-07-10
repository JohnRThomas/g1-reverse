/* Reconstructed FUN_00081a60 @ 0x81a60  (parity: 300/300 trials, PROVEN) */

extern void FUN_00081720(void);
extern int bt_l2cap_le_lookup_tx_cid(unsigned int, unsigned short);

void FUN_00081a60(unsigned int param_1, void *param_2, int param_3)
{
    if (param_3 == 0) {
        int iVar1 = bt_l2cap_le_lookup_tx_cid(param_1, *(volatile unsigned short*)((char*)param_2 + 4));
        if (iVar1 != 0) {
            FUN_00081720();
            return;
        }
    }
}

