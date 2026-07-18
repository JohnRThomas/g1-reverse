#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000868c2 @ 0x000868c2
 * public-name: malloc_impl
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed malloc_impl @ 0x000868c2 (parity: 300/300 trials, PROVEN).
 * Raw backmap: FUN_000868c2@0x000868c2. */
#include <stddef.h>

extern void *g1_recon_k_aligned_alloc_asserting(size_t alignment, size_t size); /* FUN_000758cc@0x000758cc */

void *malloc_impl(size_t size)
{
    return g1_recon_k_aligned_alloc_asserting(4u, size);
}
