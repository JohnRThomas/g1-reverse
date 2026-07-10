#include "g1_net_symbols.h"
/* net-core FUN_0100d5c8 @ 0x100d5c8  (parity 300 trials PROVEN) */

extern void FUN_0101e1e4(int,int);
void FUN_0100d5c8(int param_1, int param_2) {
    *(volatile unsigned char *)(param_1 + 0x72) = (unsigned char)param_2;
    FUN_0101e1e4(param_1, param_2);
}

