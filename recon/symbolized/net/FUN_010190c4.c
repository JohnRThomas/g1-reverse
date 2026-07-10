#include "g1_net_symbols.h"
/* net-core FUN_010190c4 @ 0x10190c4  (parity 300 trials PROVEN) */

unsigned char FUN_010190c4(void) {
    return *(volatile unsigned char *)(((uintptr_t)&g_sdc_conn_ctx) /*=0x21000f90*/ + 0x54);
}

