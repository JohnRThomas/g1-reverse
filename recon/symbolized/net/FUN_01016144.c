#include "g1_net_symbols.h"
/* net-core controller_radio_event1_dispatch @ 0x1016144
 * Missing internal tail-dispatch target recovered as a first-class function.
 * Reachable code is [0x1016144,0x101615a); 0x101615a is alignment, the
 * global-base literal occupies [0x101615c,0x1016160), and the next function
 * starts at 0x1016160. FUN_01013650 case one branches here with context/event.
 * Raw backmap: FUN_01016144@0x01016144. */
#include <stdint.h>

extern void controller_radio_idle_event_finish(void *context, uint32_t event); /* FUN_0100b594@0x0100b594 */
extern void sdc_conn_event_process(uint32_t argument, uint32_t flags);          /* FUN_01014b18@0x01014b18 */

#define G_NET_LINK_CTX_A_ADDR ((unsigned long)&g_net_link_ctx_a) /*=0x21000f68*/ /* g_net_link_ctx_a */
#define LINK_ACTIVE_OFFSET    0x2eeu

void controller_radio_event1_dispatch(void *context, uint32_t event)
{
    volatile uintptr_t *owner_slot =
        (volatile uintptr_t *)G_NET_LINK_CTX_A_ADDR;
    uintptr_t owner = owner_slot[1];

    if (*(volatile uint8_t *)(owner + LINK_ACTIVE_OFFSET) == 0) {
        controller_radio_idle_event_finish(context, event);
        return;
    }
    sdc_conn_event_process(0, 0);
}
