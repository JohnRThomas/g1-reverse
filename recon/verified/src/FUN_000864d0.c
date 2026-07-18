/* Reconstructed g1_recon_tagged_heap_node_release @ 0x000864d0.
 * Raw backmap: FUN_000864d0@0x000864d0. */

#include <stdint.h>

extern void g1_recon_k_free(void *allocation);

uintptr_t g1_recon_tagged_heap_node_release(unsigned *node, int release)
{
    uintptr_t result = (uintptr_t)node;

    if (node != 0 && ((*node & 3u) != 0u)) {
        result = node[1];
        if (release != 0) {
            g1_recon_k_free(node);
        }
    }
    return result;
}
