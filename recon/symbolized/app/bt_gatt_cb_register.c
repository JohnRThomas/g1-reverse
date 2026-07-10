#include "g1_app_symbols.h"
/* named: bt_gatt_cb_register */
/* Reconstructed bt_gatt_cb_register @ 0x5a9d8  (parity: 300/300 trials, PROVEN) */

void bt_gatt_cb_register(void *param_1)
{
    *(volatile unsigned int*)((char*)param_1 + 4) = 0;
    unsigned int node = (unsigned int)((char*)param_1 + 4);
    unsigned int base = ((uintptr_t)&g_bt_gatt_callback_list_head) /*=0x2000af10*/;
    unsigned int tail = *(volatile unsigned int*)(base + 4);
    if (tail == 0) {
        *(volatile unsigned int*)base = node;
        *(volatile unsigned int*)(base + 4) = node;
    } else {
        *(volatile unsigned int*)tail = node;
        *(volatile unsigned int*)(base + 4) = node;
    }
}

