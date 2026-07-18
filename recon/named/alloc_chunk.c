/* readable reconstruction; identity: FUN_0007df24 @ 0x0007df24
 * public-name: alloc_chunk
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   alloc_chunk                              <= FUN_0007df24 @ 0x0007df24
 */
/* CPUAPP Zephyr alloc_chunk @ 0x0007df24.
 * Raw/address back-map: FUN_0007df24 / 0x0007df24.
 */
#include <stdint.h>
extern int bucket_idx(uint32_t); /* FUN_0007de82 */
extern uint32_t chunk_size(void *, uint32_t); /* FUN_0007de18 */
extern uint32_t next_free_chunk(void *, uint32_t, uint32_t); /* FUN_0007ddec */
extern void free_list_remove_bidx(void *, uint32_t, int); /* FUN_0007de9a */
#define alloc_chunk alloc_chunk

uint32_t alloc_chunk(uint8_t *heap, uint32_t requested_size)
{
    int bucket_index = bucket_idx(*(uint32_t *)(heap + 8));
    uint32_t *bucket_next = (uint32_t *)(heap + 0x10 + bucket_index * 4);
    uint32_t first = *bucket_next;
    if (first != 0) {
        int remaining = 3;
        do {
            uint32_t chunk = *bucket_next;
            if (chunk_size(heap, chunk) >= requested_size) {
                free_list_remove_bidx(heap, chunk, bucket_index);
                return chunk;
            }
            *bucket_next = next_free_chunk(heap, chunk, 3);
        } while (--remaining != 0 && *bucket_next != first);
    }
    uint32_t mask = *(uint32_t *)(heap + 0x0c) << (bucket_index + 1);
    if (mask != 0) {
        int next_bucket = __builtin_ctz(mask) + bucket_index + 1;
        uint32_t chunk = *(uint32_t *)(heap + 0x10 + next_bucket * 4);
        free_list_remove_bidx(heap, chunk, next_bucket);
        return chunk;
    }
    return 0;
}
