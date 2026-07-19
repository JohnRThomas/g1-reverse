#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_mpsc_pbuf_buffer__param_0133           [param_0133; library]
 * Raw function identity: 0x0007e390.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0007e390 @ 0x0007e390
 * public-name: add_skip_item
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   add_skip_item                            <= FUN_0007e390 @ 0x0007e390
 */
/* CPUAPP Zephyr mpsc_pbuf add_skip_item @ 0x0007e390.
 * Raw/address back-map: FUN_0007e390 / 0x0007e390.
 */
#include <stdint.h>
extern uint32_t idx_inc(uint32_t *, uint32_t, int32_t); /* FUN_0007e35c */
#define add_skip_item add_skip_item

void add_skip_item(uint32_t *buffer, int32_t word_length)
{
    uint32_t *storage = (uint32_t *)(uintptr_t)buffer[8];

    storage[buffer[0]] = ((uint32_t)word_length << 2) | 2u;
    buffer[0] = idx_inc(buffer, buffer[0], word_length);
    if (buffer[0] == buffer[3])
        buffer[4] |= 8u;
    buffer[1] = idx_inc(buffer, buffer[1], word_length);
}
