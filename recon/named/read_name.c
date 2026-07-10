/* named: read_name */
/* Reconstructed read_name @ 0x829f0  (parity: 300/300 trials, PROVEN) */

extern int strlen(void);
extern int bt_dev_get(void);
extern void bt_gatt_attr_read.constprop.0(int,int,int,int);
void read_name(int param_1,int param_2,int param_3,int param_4,short param_5)
{
    int uVar1 = bt_dev_get();
    int r0 = strlen();
    unsigned short u = (unsigned short)r0;
    bt_gatt_attr_read.constprop.0(param_3, param_4, (int)u, uVar1);
}

