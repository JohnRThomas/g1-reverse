/* named: bt_gatt_attr_read_service */
/* Reconstructed bt_gatt_attr_read_service @ 0x82988  (parity: 300/300 trials, PROVEN) */

extern void bt_gatt_attr_read.constprop.0(int a, int b, int c, int d, ...);

void bt_gatt_attr_read_service(void *param_1, char *param_2, int param_3, int param_4, unsigned short param_5)
{
    char *pcVar1;
    pcVar1 = *(char **)(param_2 + 0xc);
    if (*pcVar1 != 0) {
        bt_gatt_attr_read.constprop.0(param_3, param_4, param_5, (int)(pcVar1 + 1));
        return;
    }
    bt_gatt_attr_read.constprop.0(param_3, param_4, param_5, 0, 2, (int)param_2, param_3, 0);
}

