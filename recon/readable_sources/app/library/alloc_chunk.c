#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_sys_heap_chunk__param_0493             [param_0493; library]
 * Raw function identity: 0x0007df24.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0007df24 @ 0x0007df24
 * public-name: alloc_chunk
 * durable-map: recon/catalogs/function_names_app.json
 */
/* CPUAPP Zephyr alloc_chunk @ 0x0007df24.
 * Raw/address back-map: FUN_0007df24 / 0x0007df24.
 */
#include <stdint.h>
extern int bucket_idx(uint32_t); /* FUN_0007de82 */
extern uint32_t chunk_size(void *, uint32_t); /* FUN_0007de18 */
extern uint32_t next_free_chunk(void *, uint32_t, uint32_t); /* FUN_0007ddec */
#ifdef G1_APP_SDK_INLINE_COHESION
extern uint32_t chunk_field(const void *, uint32_t, uint32_t); /* FUN_0007ddec */
extern void chunk_set(void *, uint32_t, uint32_t, uint32_t); /* FUN_0007de02 */

/* Exact Zephyr 3.4.99 heap.c local owner; raw FUN_0007de9a @ 0x0007de9a.
 * This stays TU-local in the cohesive build.  The parity build below retains
 * the historical BL as an independent oracle boundary.
 */
static __attribute__((always_inline)) inline void free_list_remove_bidx(
    void *heap_arg, uint32_t chunk, int bucket_index)
{
    uint8_t *heap = (uint8_t *)heap_arg;
    uint32_t next = chunk_field(heap, chunk, 3u);

    if (next == chunk) {
        *(uint32_t *)(heap + 0x0cu) &= ~(1u << (bucket_index & 0xff));
        *(uint32_t *)(heap + 0x10u + (uint32_t)bucket_index * 4u) = 0u;
    } else {
        uint32_t previous = chunk_field(heap, chunk, 2u);
        *(uint32_t *)(heap + 0x10u + (uint32_t)bucket_index * 4u) = next;
        chunk_set(heap, previous, 3u, next);
        chunk_set(heap, next, 2u, previous);
    }
}
#else
extern void free_list_remove_bidx(void *, uint32_t, int); /* FUN_0007de9a */
#endif
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
