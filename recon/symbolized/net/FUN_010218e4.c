#include "g1_net_symbols.h"
/* net-core FUN_010218e4 @ 0x10218e4  (parity 300 trials PROVEN) */

#include <stdint.h>
typedef long long (*code)(void);
void FUN_010218e4(void) {
    uint32_t v = *(volatile uint32_t*)((uintptr_t)&g_net_radio_ops_table_ptr) /*=0x21000530*/;
    code fn = *(code*)(v + 0x14);
    fn();
}

