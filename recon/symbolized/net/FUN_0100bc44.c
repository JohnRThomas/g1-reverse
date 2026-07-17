#include "g1_net_symbols.h"
/* net-core FUN_0100bc44 @ 0x100bc44  (parity 300 trials PROVEN) */

void FUN_0100bc44(unsigned char param_1) {
    *(volatile unsigned char *)(((unsigned long)&g_net_radio_addr_match_tbl) /*=0x21000d18*/ + 0x18b) = param_1;
}
