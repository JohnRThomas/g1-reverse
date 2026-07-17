#include "g1_net_symbols.h"
/* net-core FUN_010397c0 @ 0x10397c0  (parity 300 trials PROVEN) */

unsigned int FUN_010397c0(unsigned int param_1, int param_2)
{
    int iVar1;
    if (param_1 < 0x8000) {
        iVar1 = 4;
    } else {
        iVar1 = 8;
    }
    return (unsigned int)(param_2 + 7 + iVar1) >> 3;
}
