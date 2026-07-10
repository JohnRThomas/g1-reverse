#include "g1_app_symbols.h"
/* named: bt_gatt_dm_attr_chrc_val */
/* Reconstructed bt_gatt_dm_attr_chrc_val @ 0x7f4a0  (parity: 300/300 trials, PROVEN) */

extern int bt_uuid_cmp(void *a, int b, unsigned int c, unsigned int d, void *e);

int bt_gatt_dm_attr_chrc_val(int *param_1, unsigned short param_2, unsigned int param_3)
{
    int iVar2 = 0;
    int iVar1;
    unsigned short local_14 = (unsigned short)(param_2 & ((uintptr_t)&rodata_ff00) /*=0xff00*/);
    unsigned short local_12 = 0x2803;
    unsigned int uStack_10 = param_3;
    (void)local_12; (void)uStack_10;
    iVar1 = bt_uuid_cmp(&local_14, *param_1, param_3, 0x2803, param_1);
    if (iVar1 == 0) {
        iVar2 = *param_1 - 8;
    }
    return iVar2;
}

