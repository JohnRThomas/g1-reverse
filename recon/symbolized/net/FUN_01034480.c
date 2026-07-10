#include "g1_net_symbols.h"
/* net-core FUN_01034480 @ 0x1034480  (parity 300 trials PROVEN) */

#include <stdint.h>
extern void FUN_01034328(uint32_t, uint32_t);
void FUN_01034480(uint32_t param_1) {
    FUN_01034328(((uintptr_t)&g_net_dppi_chan_ctx) /*=0x210006a0*/, param_1);
}

