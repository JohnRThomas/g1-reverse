#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007d894 @ 0x0007d894
 * public-name: u32_to_bytes_le_array
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   u32_to_bytes_le_array                    <= FUN_0007d894 @ 0x0007d894
 */
/* Reconstructed FUN_0007d894 @ 0x7d894. */
#include <stdint.h>

/* Copy little-endian 32-bit words bytewise.  Like the firmware, a non-multiple
 * of four byte count still copies the complete final word. */
void u32_to_bytes_le_array(uint8_t *dst, const uint8_t *src, uint32_t byte_count)
{
    uint32_t copied = 0;

    while (copied < byte_count) {
        dst[copied] = src[copied];
        dst[copied + 1] = src[copied + 1];
        dst[copied + 2] = src[copied + 2];
        dst[copied + 3] = src[copied + 3];
        copied += 4;
    }
}
