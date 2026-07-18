/* Reconstructed malloc_impl @ 0x000868c2 (parity: 300/300 trials, PROVEN).
 * Raw backmap: FUN_000868c2@0x000868c2. */
#include <stddef.h>

#define k_aligned_alloc FUN_000758cc
extern void *k_aligned_alloc(size_t alignment, size_t size); /* FUN_000758cc@0x000758cc */

void *malloc_impl(size_t size)
{
    return k_aligned_alloc(4u, size);
}
