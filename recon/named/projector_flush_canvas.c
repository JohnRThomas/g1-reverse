#include "g1_app_symbols.h"
/* readable reconstruction; identity: projector_flush_canvas @ 0x0007d4d6
 * public-name: projector_flush_canvas
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   projector_write_pixel_data               <= FUN_0007d70a @ 0x0007d70a
 */
/* Reconstructed projector_flush_canvas @ 0x7d4d6 (uncatalogued: Ghidra folded
 * it into the tail of get_localized_weekday_name; code 0x7d4d6..0x7d4ec).
 * (parity: cfg_verify PASS, 200/200 trials)
 * Vtable slot +0x18 (device_ctx + 0xb84) written by quicknote_buffer_pool_init.
 * Gated on the panel-on flag ctx+0x35c; on the early-out path the original
 * leaves r0 untouched, i.e. returns its own argument.
 */
#include <stdint.h>

extern uint32_t projector_write_pixel_data(uint32_t x, uint32_t y, uint32_t buf, uint32_t length);

uint32_t projector_flush_canvas(uint8_t *context)
{
    if (*(volatile uint32_t *)(context + 0x35c) == 0)
        return (uint32_t)context;
    return projector_write_pixel_data(*(volatile uint32_t *)(context + 0x348),
                                      *(volatile uint32_t *)(context + 0x34c),
                                      *(volatile uint32_t *)(context + 0x24),
                                      *(volatile uint32_t *)(context + 0x350));
}
