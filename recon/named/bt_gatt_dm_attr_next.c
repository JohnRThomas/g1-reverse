/* named: bt_gatt_dm_attr_next */
/* Reconstructed bt_gatt_dm_attr_next @ 0x7f51a  (parity: 300/300 trials, PROVEN) */

typedef unsigned int uint;
uint bt_gatt_dm_attr_next(char *param_1, uint param_2)
{
    uint uVar1;
    uVar1 = (uint)(unsigned long)(param_1 + 0x1c);
    if (param_2 != 0) {
        if (param_2 < uVar1) {
            return 0;
        }
        uVar1 = param_2;
    }
    uVar1 = uVar1 + 8;
    if ((uint)(unsigned long)(param_1 + (*(volatile int*)(param_1 + 0x134)) * 8 + 0x1c) <= uVar1) {
        uVar1 = 0;
    }
    return uVar1;
}

