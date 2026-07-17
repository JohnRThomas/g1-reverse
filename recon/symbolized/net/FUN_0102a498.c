#include "g1_net_symbols.h"
/* net-core FUN_0102a498 @ 0x102a498  (parity 300 trials PROVEN) */

#include <stdint.h>
static volatile uint32_t * const DAT_0102a4a0 = (volatile uint32_t *)((unsigned long)&g_sdc_hci_transport_obj) /*=0x210045f4*/;
uint32_t FUN_0102a498(void) {
    uint32_t p = *DAT_0102a4a0;
    return *(uint32_t*)(p + 4);
}
