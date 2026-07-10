#include "g1_net_symbols.h"
/* net-core FUN_010107a0 @ 0x10107a0  (parity 300 trials PROVEN) */

void FUN_010107a0(void) {
    *(volatile unsigned char *)((uintptr_t)&g_net_lookup_table_desc) /*=0x21000f14*/ = 0;
}

