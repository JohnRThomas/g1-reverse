#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0102583c @ 0x0102583c
 * public-name: controller_deferred_event_raise
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   controller_deferred_event_raise          <= FUN_0102583c @ 0x0102583c
 */
/* net-core FUN_0102583c @ 0x0102583c -- raw backmap retained. */
#include <stdint.h>

extern __attribute__((noreturn)) void FUN_010256dc(uint32_t, uint32_t, ...);
extern void FUN_01025734(void);
#define controller_fault FUN_010256dc

void controller_deferred_event_raise(uint32_t event)
{
    volatile uint8_t *const slots = (volatile uint8_t *)G1N_21001c24;

    if (event > 4)
        controller_fault(0x69, 0x58);
    volatile uint8_t *slot = slots + event * 8u;
    if (slot[4] != 1)
        controller_fault(0x69, 0x59);
    uint8_t next = (uint8_t)(slot[5] + 1u);
    if (slot[6] != next)
        slot[5] = next;
    FUN_01025734();
}
