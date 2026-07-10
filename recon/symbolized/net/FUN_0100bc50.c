#include "g1_net_symbols.h"
/* net-core FUN_0100bc50 @ 0x100bc50  (parity 300 trials PROVEN) */

unsigned char FUN_0100bc50(void) {
    return *(volatile unsigned char *)(((uintptr_t)&g_net_radio_addr_match_tbl) /*=0x21000d18*/ + 0x18b);
}

