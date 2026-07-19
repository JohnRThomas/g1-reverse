#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_nrfx_spim_cb__param_0690               [param_0690; library]
 * Raw function identity: 0x000852ba.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_000852ba @ 0x000852ba
 * public-name: spim_abort
 * durable-map: recon/catalogs/function_names_app.json
 */
/* NCS 2.5.1 spim_abort @ 0x000852ba (FUN_000852ba). */
#include <stdint.h>

extern uint32_t __nrfy_internal_spim_events_process(
    volatile uint8_t *spim, uint32_t event_mask, void *events); /* FUN_0008523e */
extern void nrfx_busy_wait(uint32_t microseconds); /* thunk_FUN_00086384 */

void spim_abort(volatile uint8_t *spim, uint8_t *control_block)
{
    *(volatile uint32_t *)(spim + 0x14) = 1u;
    uint32_t attempts = 100u;
    do {
        if (__nrfy_internal_spim_events_process(spim, 2u, 0) != 0u) {
            break;
        }
        nrfx_busy_wait(1u);
    } while (--attempts != 0u);
    control_block[0x1d] = 0u;
    *(volatile uint32_t *)(spim + 0x500) = 0u;
}
