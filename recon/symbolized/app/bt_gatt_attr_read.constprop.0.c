#include "g1_app_symbols.h"
/* named: bt_gatt_attr_read.constprop.0 */
/* Reconstructed bt_gatt_attr_read.constprop.0 @ 0x82932  (parity: 300/300 trials, PROVEN) */

typedef unsigned int uint;
extern void memcpy(unsigned int a, unsigned int b, unsigned int c, int d, int e);

uint bt_gatt_attr_read_constprop_0(unsigned int param_1, uint param_2, uint param_3, int param_4, unsigned short param_5) __asm__("bt_gatt_attr_read.constprop.0");
uint bt_gatt_attr_read_constprop_0(unsigned int param_1, uint param_2, uint param_3, int param_4, unsigned short param_5)
{
    uint uVar1;
    if (param_5 < param_3) {
        uVar1 = 0xfffffff9;
    } else {
        uVar1 = param_5 - param_3;
        if ((int)param_2 <= (int)uVar1) {
            uVar1 = param_2;
        }
        uVar1 = uVar1 & ((uintptr_t)&tbl_ffc8) /*=0xffff*/;
        memcpy(param_1, param_4 + param_3, uVar1, param_4, param_4);
    }
    return uVar1;
}

