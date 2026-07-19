/* readable reconstruction; identity: FUN_0007e0a6 @ 0x0007e0a6
 * public-name: free_chunk
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   chunk_field                              <= FUN_0007ddec @ 0x0007ddec
 *   chunk_set                                <= FUN_0007de02 @ 0x0007de02
 *   chunk_size                               <= FUN_0007de18 @ 0x0007de18
 *   chunk_set_used_flag                      <= FUN_0007de54 @ 0x0007de54
 *   heap_bucket_index                        <= FUN_0007de82 @ 0x0007de82
 *   merge_chunks                             <= FUN_0007dfe6 @ 0x0007dfe6
 *   free_list_add                            <= FUN_0007e022 @ 0x0007e022
 */
/* Reconstructed Zephyr free_chunk @ 0x0007e0a6.
 * Raw/address back-map: FUN_0007e0a6 / 0x0007e0a6.
 */
#include <stdint.h>

extern uint32_t chunk_size(void *heap, uint32_t chunk);
extern uint32_t chunk_field(void *heap, uint32_t chunk, uint32_t side);
#ifdef G1_APP_SDK_INLINE_COHESION
extern int heap_bucket_index(uint32_t end_chunk, uint32_t size);
extern void chunk_set(void *heap, uint32_t chunk, uint32_t field,
                         uint32_t value);
extern void chunk_set_used_flag(void *heap, uint32_t chunk, uint32_t size);

/* Exact Zephyr 3.4.99 heap.c locals.  They are always-inline and TU-local so
 * the cohesive build exports no duplicate helper owner; parity mode keeps the
 * original call boundaries through the extern branch below.
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

static __attribute__((always_inline)) inline void free_list_remove(
    void *heap_arg, uint32_t chunk)
{
    uint8_t *heap = (uint8_t *)heap_arg;
    uint32_t size = chunk_size(heap, chunk);

    if (*(uint32_t *)(heap + 8u) >= 0x8000u && size == 1u)
        return;
    free_list_remove_bidx(heap, chunk,
                          heap_bucket_index(*(uint32_t *)(heap + 8u), size));
}

static __attribute__((always_inline)) inline void merge_chunks(
    void *heap, uint32_t left, uint32_t right)
{
    uint32_t merged = chunk_size(heap, left) +
                      chunk_size(heap, right);
    chunk_set_used_flag(heap, left, merged);
    chunk_set(heap, right + chunk_size(heap, right), 0u, merged);
}
#else
extern void FUN_0007def6(void *heap, uint32_t chunk);
extern void merge_chunks(void *heap, uint32_t left, uint32_t right);
#define free_list_remove FUN_0007def6
#define merge_chunks merge_chunks
#endif
extern void free_list_add(void *heap, uint32_t chunk);

void free_chunk(void *heap, uint32_t chunk)
{
    uint32_t right = chunk + chunk_size(heap, chunk);

    if ((chunk_field(heap, right, 1) & 1u) == 0u) {
        free_list_remove(heap, right);
        merge_chunks(heap, chunk, chunk + chunk_size(heap, chunk));
    }

    uint32_t left = chunk - chunk_field(heap, chunk, 0);
    if ((chunk_field(heap, left, 1) & 1u) == 0u) {
        free_list_remove(heap, left);
        merge_chunks(heap, chunk - chunk_field(heap, chunk, 0), chunk);
        chunk -= chunk_field(heap, chunk, 0);
    }

    free_list_add(heap, chunk);
}
