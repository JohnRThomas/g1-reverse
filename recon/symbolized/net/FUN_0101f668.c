#include "g1_net_symbols.h"
/* net-core FUN_0101f668 @ 0x101f668  (parity 300 trials PROVEN) */

unsigned int FUN_0101f668(unsigned char param_1) {
    *(volatile unsigned char *)(((unsigned long)&g_net_ble_conn_role_cfg) /*=0x21001208*/ + 0x18) = param_1;
    return 0;
}
