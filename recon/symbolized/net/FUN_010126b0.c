#include "g1_net_symbols.h"
/* net-core FUN_010126b0 @ 0x10126b0  (parity 300 trials PROVEN) */

unsigned short FUN_010126b0(int param_1) {
    return *(unsigned short *)(param_1 + 2) & 1;
}
