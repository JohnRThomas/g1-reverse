/* Reconstructed chunk_size @ 0x7de18  (CFG-directed candidate) */
/* Owner: Zephyr 3.4.99 lib/os/heap.h; raw backmap FUN_0007de18@0x0007de18. */
#include <stdint.h>
extern uint32_t chunk_field(const void *heap, uint32_t chunk, uint32_t field);
unsigned long chunk_size(void*heap, unsigned long chunk) {
    return chunk_field(heap, chunk, 1u) >> 1;
}
