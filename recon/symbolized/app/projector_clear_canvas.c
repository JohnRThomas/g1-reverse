#include "g1_app_symbols.h"
/* readable reconstruction; identity: projector_clear_canvas @ 0x0007d4ca
 * public-name: projector_clear_canvas
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 */
/* Reconstructed projector_clear_canvas @ 0x7d4ca (uncatalogued: Ghidra folded
 * it into the tail of get_localized_weekday_name; code 0x7d4ca..0x7d4d6).
 * (parity: cfg_verify PASS, 200/200 trials)
 * Vtable slot +0x1c (device_ctx + 0xb88) written by quicknote_buffer_pool_init.
 */
#include <stdint.h>

extern uint32_t memset_bytes(uint32_t dst, uint32_t value, uint32_t length);

uint32_t projector_clear_canvas(uint8_t *context)
{
    return memset_bytes(*(volatile uint32_t *)(context + 0x24), 0,
                        *(volatile uint32_t *)(context + 0x350));
}
