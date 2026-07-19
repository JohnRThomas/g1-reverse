#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_2          => struct g1_layout_u32le_array__param_0486                [param_0486; G1-original]
 * Raw function identity: 0x0007d8c4.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0007d8c4 @ 0x0007d8c4
 * public-name: bytes_to_u32le_array
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bytes_to_u32le_array                     <= FUN_0007d8c4 @ 0x0007d8c4
 */
/* Reconstructed FUN_0007d8c4 @ 0x7d8c4. */
#include <stdint.h>

/* Assemble little-endian input bytes into aligned destination words. */
void bytes_to_u32le_array(uint32_t *dst, const uint8_t *src, uint32_t byte_count)
{
    uint32_t offset = 0;

    while (offset < byte_count) {
        uint32_t word = (uint32_t)src[offset]
                      | (uint32_t)src[offset + 1] << 8
                      | (uint32_t)src[offset + 2] << 16
                      | (uint32_t)src[offset + 3] << 24;
        dst[offset / 4] = word;
        offset += 4;
    }
}
