#include "g1_app_symbols.h"
/* named: cf_read */
/* Reconstructed cf_read @ 0x829c0  (parity: 300/300 trials, PROVEN) */

extern int find_cf_cfg(void);
extern void bt_gatt_attr_read_constprop_0(unsigned int a, unsigned int b, unsigned short c, void *d, int e) __asm__("bt_gatt_attr_read.constprop.0");

void cf_read(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4, unsigned short param_5)
{
    unsigned char local_14[8];
    local_14[0] = 0;
    int iVar1 = find_cf_cfg();
    if (iVar1 != 0) {
        local_14[0] = *(volatile unsigned char*)((char*)iVar1 + 8);
    }
    bt_gatt_attr_read_constprop_0(param_3, param_4, param_5, local_14, 1);
}

