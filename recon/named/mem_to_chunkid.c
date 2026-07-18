/* readable reconstruction; identity: FUN_0007de5c @ 0x0007de5c
 * public-name: mem_to_chunkid
 * durable-map: recon/catalogs/function_names_app.json
 */
/* mem_to_chunkid @ 0x0007de5c; raw FUN_0007de5c */
#include <stdint.h>

uint32_t mem_to_chunkid(uint8_t *heap, void *memory)
{
    uintptr_t header = *(uint32_t *)(heap + 8) < 0x8000u ? 4u : 8u;
    return (uint32_t)(((uintptr_t)memory - header - (uintptr_t)heap) >> 3);
}
