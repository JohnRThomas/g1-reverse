#include "g1_net_symbols.h"
/* net-core FUN_0101deb8 @ 0x101deb8  (parity 300 trials PROVEN) */

void FUN_0101deb8(void) {
    *(volatile unsigned char *)(((uintptr_t)&g_timeout_list) /*=0x2100113c*/ + 4) = 0;
}

