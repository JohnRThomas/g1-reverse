#include "g1_net_symbols.h"
/* net-core FUN_0101f888 @ 0x101f888  (parity 300 trials PROVEN) */

unsigned char FUN_0101f888(void) {
    return *(volatile unsigned char *)(((uintptr_t)&g_net_sdc_resource_cfg) /*=0x21001230*/ + 0x219);
}

