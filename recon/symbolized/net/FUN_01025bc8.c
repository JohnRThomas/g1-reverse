#include "g1_net_symbols.h"
/* net-core FUN_01025bc8 @ 0x1025bc8  (parity 300 trials PROVEN) */

#include <stdint.h>
typedef long long (*code)(void);
void FUN_01025bc8(void) {
    uint32_t v = *(volatile uint32_t*)((uintptr_t)&g_net_driver_api_ptr) /*=0x21000574*/;
    code fn = *(code*)(v + 8);
    fn();
}

