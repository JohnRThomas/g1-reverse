#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01039a7a @ 0x01039a7a
 * public-name: FUN_01039a7a
 * durable-map: recon/catalogs/function_names_net.json
 */
/* CPUNET Zephyr sys_heap_alloc @ 0x01039a7a.
 * Raw/address back-map: FUN_01039a7a / 0x01039a7a.
 */
#include <stddef.h>
#include <stdint.h>

extern uint32_t bytes_to_chunksz(uint32_t, size_t); /* FUN_010397c0 */
extern uint32_t alloc_chunk(void *, uint32_t); /* FUN_01039874 */
extern uint32_t chunk_size(void *, uint32_t); /* FUN_01039768 */
extern void split_chunks(void *, uint32_t, uint32_t); /* FUN_010398e8 */
extern void free_list_add(void *, uint32_t); /* FUN_01039972 */
extern void *set_chunk_used(void *, uint32_t, int); /* FUN_01039774 */
#define sys_heap_alloc FUN_01039a7a

void *sys_heap_alloc(uint32_t **heap, size_t bytes)
{
    uint32_t *h = *heap;

    if (bytes == 0 || h[2] <= (bytes >> 3))
        return 0;

    uint32_t chunk_words = bytes_to_chunksz(h[2], bytes);
    uint32_t chunk = alloc_chunk(h, chunk_words);
    if (chunk == 0)
        return 0;

    if (chunk_size(h, chunk) > chunk_words) {
        split_chunks(h, chunk, chunk + chunk_words);
        free_list_add(h, chunk + chunk_words);
    }

    /* GCC keeps the unchanged heap pointer in r0 across this static helper;
     * model that firmware register contract explicitly for oracle parity. */
    void *memory_base = set_chunk_used(h, chunk, 1);
    uintptr_t header_size = h[2] < 0x8000u ? 4u : 8u;
    return (uint8_t *)memory_base + header_size + chunk * 8u;
}
