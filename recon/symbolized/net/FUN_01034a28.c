#include "g1_net_symbols.h"
/* net-core FUN_01034a28 @ 0x1034a28  (parity 300 trials PROVEN) */

#include <stdint.h>
extern void FUN_01034368(uint32_t, uint32_t);
void FUN_01034a28(uint32_t param_1) {
    FUN_01034368(((uintptr_t)&g_net_conn_teardown_ctx_a) /*=0x21000718*/, param_1);
}

