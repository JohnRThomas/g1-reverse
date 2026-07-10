/* Reconstructed FUN_000829f0 @ 0x829f0  (parity: 300/300 trials, PROVEN) */

extern int strlen(void);
extern int FUN_00054ce0(void);
extern void bt_gatt_attr_read_constprop_0(int,int,int,int);
void read_name(int param_1,int param_2,int param_3,int param_4,short param_5)
{
    int uVar1 = FUN_00054ce0();
    int r0 = strlen();
    unsigned short u = (unsigned short)r0;
    bt_gatt_attr_read_constprop_0(param_3, param_4, (int)u, uVar1);
}

