#include "g1_net_symbols.h"
/* net-core FUN_01025bbc @ 0x1025bbc  (parity 300 trials PROVEN) */

#include <stdint.h>
typedef long long (*code)(void);
void FUN_01025bbc(void) {
    uint32_t v = *(volatile uint32_t*)((unsigned long)&g_net_driver_api_ptr) /*=0x21000574*/;
    code fn = *(code*)(v + 4);
    fn();
}
