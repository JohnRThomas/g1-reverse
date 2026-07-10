#include "g1_net_symbols.h"
/* net-core FUN_0101f650 @ 0x101f650  (parity 300 trials PROVEN) */

unsigned int FUN_0101f650(unsigned int *param_1, unsigned int param_2, int param_3)
{
    unsigned int uVar2 = *param_1;
    unsigned int uVar1;
    if (uVar2 >= 1000) {
        uVar1 = 0;
        param_3 = ((uintptr_t)&g_net_ble_conn_create_ctx) /*=0x21000eac*/;
        *(unsigned int *)(param_3 + 8) = uVar2;
    } else {
        uVar1 = 0x12;
    }
    return uVar1;
}

