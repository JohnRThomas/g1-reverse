#include "g1_net_symbols.h"
/* net-core FUN_01021908 @ 0x1021908  (parity 300 trials PROVEN) */

#include <stdint.h>
typedef long long (*code)(void);
void FUN_01021908(void) {
    uint32_t v = *(volatile uint32_t*)((uintptr_t)&g_net_radio_ops_table_ptr) /*=0x21000530*/;
    code fn = *(code*)(v + 0x28);
    fn();
}

