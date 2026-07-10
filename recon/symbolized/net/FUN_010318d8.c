#include "g1_net_symbols.h"
/* net-core FUN_010318d8 @ 0x10318d8  (parity 300 trials PROVEN) */

#include <stdint.h>
extern void FUN_0103b268(uint32_t, uint32_t);
void FUN_010318d8(void) {
    FUN_0103b268(((uintptr_t)&g_net_sync_obj_a) /*=0x210042f0*/, ((uintptr_t)&g_net_config_record_copy_dst) /*=0x21004974*/);
}

