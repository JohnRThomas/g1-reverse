#include "g1_net_symbols.h"
/* net-core FUN_0101f87c @ 0x101f87c  (parity 300 trials PROVEN) */

void FUN_0101f87c(unsigned char param_1) {
    *(volatile unsigned char *)(((uintptr_t)&g_net_sdc_resource_cfg) /*=0x21001230*/ + 0x219) = param_1;
}

