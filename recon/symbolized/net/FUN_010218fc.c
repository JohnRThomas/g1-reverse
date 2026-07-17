#include "g1_net_symbols.h"
/* net-core FUN_010218fc @ 0x10218fc  (parity 300 trials PROVEN) */

#include <stdint.h>
typedef long long (*code)(void);
void FUN_010218fc(void) {
    uint32_t v = *(volatile uint32_t*)((unsigned long)&g_net_radio_ops_table_ptr) /*=0x21000530*/;
    code fn = *(code*)(v + 0x24);
    fn();
}
