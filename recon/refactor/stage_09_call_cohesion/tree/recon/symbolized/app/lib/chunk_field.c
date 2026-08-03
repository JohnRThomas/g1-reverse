#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007ddec @ 0x0007ddec
 * public-name: chunk_field
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed chunk_field @ 0x7ddec  (CFG-directed candidate) */
/* Owner: Zephyr 3.4.99 lib/os/heap.h; raw backmap FUN_0007ddec@0x0007ddec. */
#include <stdint.h>
uint32_t chunk_field(const void *heap_arg, uint32_t chunk, uint32_t field)
{
    const uint8_t *heap = (const uint8_t *)heap_arg;
    const uint8_t *chunk_memory = heap + chunk * 8u;
    if (*(const uint32_t *)(heap + 8u) >= 0x8000u) {
        return ((const uint32_t *)chunk_memory)[field];
    }
    return ((const uint16_t *)chunk_memory)[field];
}
