#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000868b4 @ 0x000868b4
 * public-name: g1_recon_k_free
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed g1_recon_k_free @ 0x000868b4.
 * Raw backmap: FUN_000868b4@0x000868b4. */

extern void g1_recon_k_heap_free_validated(void *heap, void *memory);

void g1_recon_k_free(void *allocation)
{
    unsigned char *header;

    if (allocation == 0) {
        return;
    }
    header = (unsigned char *)allocation - 4;
    g1_recon_k_heap_free_validated(*(void **)header, header);
}
