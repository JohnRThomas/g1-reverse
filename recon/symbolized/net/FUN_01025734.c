#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01025734 @ 0x01025734
 * public-name: FUN_01025734
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_01025734 @ 0x01025734, exact Thumb extent 0x20 bytes. */
#include <stdint.h>

/* MPSL's deferred-event IRQ number; negative means no IRQ was assigned. */
static volatile int8_t *const deferred_event_irq =
    (volatile int8_t *)G1N_21001c20; /* g_21001c18 + 8 */

/* ARMv8-M NVIC interrupt-set-pending registers for external interrupt lines. */
static volatile uint32_t *const nvic_ispr =
    (volatile uint32_t *)0xe000e200u; /* 0xe000e100 + 0x100 */

#define controller_deferred_irq_set_pending FUN_01025734

void controller_deferred_irq_set_pending(void)
{
    int32_t irq = *deferred_event_irq;

    if (irq >= 0) {
        nvic_ispr[irq >> 5] = UINT32_C(1) << (irq & 31);
    }
}
