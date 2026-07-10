/* named: read_appearance */
/* Reconstructed read_appearance @ 0x82a1a  (parity: 300/300 trials, PROVEN) */

extern unsigned int FUN_00080f8c(void);
extern void bt_gatt_attr_read.constprop.0(unsigned int a, unsigned int b, unsigned int c, void *d, unsigned int e);

void read_appearance(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4, unsigned short param_5)
{
    unsigned short local_12[3];
    local_12[0] = (unsigned short)FUN_00080f8c();
    bt_gatt_attr_read.constprop.0(param_3, param_4, param_5, local_12, 2);
}

