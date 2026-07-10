#include "g1_net_symbols.h"
/* net-core FUN_0100e7c8 @ 0x100e7c8  (parity 300 trials PROVEN) */

void FUN_0100e7c8(int param_1, unsigned int param_2) {
    *(char *)(param_1 + 10) = (char)param_2;
    *(char *)(param_1 + 0xb) = (char)(param_2 >> 8);
}

