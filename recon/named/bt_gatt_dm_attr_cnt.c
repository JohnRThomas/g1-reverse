/* named: bt_gatt_dm_attr_cnt */
/* Reconstructed bt_gatt_dm_attr_cnt @ 0x7f4cc  (parity: 300/300 trials, PROVEN) */

unsigned int bt_gatt_dm_attr_cnt(char *param_1)
{
    return *(volatile unsigned int *)(param_1 + 0x134);
}

