/* readable reconstruction; identity: FUN_0007e12a @ 0x0007e12a
 * public-name: sys_heap_alloc
 * durable-map: recon/catalogs/function_names_app.json
 */
/* sys_heap_alloc @ 0x0007e12a; raw FUN_0007e12a */
#include <stddef.h>
#include <stdint.h>

extern uint32_t bytes_to_chunksz(uint32_t heap_bytes, uint32_t bytes); /* FUN_0007de70 */
extern uint32_t alloc_chunk(uint8_t *heap, uint32_t chunks); /* FUN_0007df24 */
extern uint32_t chunk_size(uint8_t *heap, uint32_t chunk); /* FUN_0007de18 */
extern void split_chunks(uint8_t *heap, uint32_t left, uint32_t right); /* FUN_0007df98 */
extern void free_list_add(uint8_t *heap, uint32_t chunk); /* FUN_0007e022 */
extern void set_chunk_used(uint8_t *heap, uint32_t chunk, int used); /* FUN_0007de24 */

void *sys_heap_alloc(void *heap_handle, size_t bytes)
{
    uint8_t *heap = *(uint8_t **)heap_handle;
    uint32_t heap_bytes;
    uint32_t required;
    uint32_t chunk;

    if (bytes == 0u) {
        return NULL;
    }
    heap_bytes = *(uint32_t *)(heap + 8);
    if (heap_bytes <= ((uint32_t)bytes >> 3)) {
        return NULL;
    }

    required = bytes_to_chunksz(heap_bytes, (uint32_t)bytes);
    chunk = alloc_chunk(heap, required);
    if (chunk == 0u) {
        return NULL;
    }
    if (chunk_size(heap, chunk) > required) {
        split_chunks(heap, chunk, chunk + required);
        free_list_add(heap, chunk + required);
    }
    set_chunk_used(heap, chunk, 1);

    return heap + (chunk << 3) + (heap_bytes < 0x8000u ? 4u : 8u);
}
