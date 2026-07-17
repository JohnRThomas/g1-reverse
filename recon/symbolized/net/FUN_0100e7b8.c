#include "g1_net_symbols.h"
/* net-core FUN_0100e7b8 @ 0x100e7b8  (parity 300 trials PROVEN) */

void FUN_0100e7b8(int param_1, unsigned int param_2) {
    *(char *)(param_1 + 6) = (char)param_2;
    *(char *)(param_1 + 7) = (char)(param_2 >> 8);
}
