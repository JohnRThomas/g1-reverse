#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007de18 @ 0x0007de18
 * public-name: chunk_size
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed chunk_size @ 0x7de18  (CFG-directed candidate) */
/* Owner: Zephyr 3.4.99 lib/os/heap.h; raw backmap FUN_0007de18@0x0007de18. */
#include <stdint.h>
#include "g1_lib.h"
unsigned long chunk_size(void*heap, unsigned long chunk) {
    return chunk_field(heap, chunk, 1u) >> 1;
}
