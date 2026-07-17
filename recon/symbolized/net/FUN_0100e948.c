#include "g1_net_symbols.h"
/* net-core FUN_0100e948 @ 0x100e948  (parity 300 trials PROVEN) */

unsigned int FUN_0100e948(unsigned int param_1)
{
    volatile unsigned char * const p = (volatile unsigned char * const)((unsigned long)&g_net_ble_conn_create_ctx) /*=0x21000eac*/;
    unsigned int r3 = (p[0x16] >> 2) & 1;
    return (param_1 | r3) ^ 1;
}
