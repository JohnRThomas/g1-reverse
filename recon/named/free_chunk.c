/* readable reconstruction; identity: FUN_0007e0a6 @ 0x0007e0a6
 * public-name: free_chunk
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   chunk_field                              <= FUN_0007ddec @ 0x0007ddec
 *   chunk_size                               <= FUN_0007de18 @ 0x0007de18
 *   merge_chunks                             <= FUN_0007dfe6 @ 0x0007dfe6
 *   free_list_add                            <= FUN_0007e022 @ 0x0007e022
 */
/* Reconstructed Zephyr free_chunk @ 0x0007e0a6.
 * Raw/address back-map: FUN_0007e0a6 / 0x0007e0a6.
 */
#include <stdint.h>

extern uint32_t chunk_size(void *heap, uint32_t chunk);
extern uint32_t chunk_field(void *heap, uint32_t chunk, uint32_t side);
extern void FUN_0007def6(void *heap, uint32_t chunk);
extern void merge_chunks(void *heap, uint32_t left, uint32_t right);
extern void free_list_add(void *heap, uint32_t chunk);

void free_chunk(void *heap, uint32_t chunk)
{
    uint32_t right = chunk + chunk_size(heap, chunk);

    if ((chunk_field(heap, right, 1) & 1u) == 0u) {
        FUN_0007def6(heap, right);
        merge_chunks(heap, chunk, chunk + chunk_size(heap, chunk));
    }

    uint32_t left = chunk - chunk_field(heap, chunk, 0);
    if ((chunk_field(heap, left, 1) & 1u) == 0u) {
        FUN_0007def6(heap, left);
        merge_chunks(heap, chunk - chunk_field(heap, chunk, 0), chunk);
        chunk -= chunk_field(heap, chunk, 0);
    }

    free_list_add(heap, chunk);
}
