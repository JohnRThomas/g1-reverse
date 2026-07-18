/* readable reconstruction; identity: FUN_000868b4 @ 0x000868b4
 * public-name: g1_recon_k_free
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   k_heap_free                              <= FUN_00071b2c @ 0x00071b2c
 */
/* Reconstructed g1_recon_k_free @ 0x000868b4.
 * Raw backmap: FUN_000868b4@0x000868b4. */

#define k_heap_free k_heap_free
extern void k_heap_free(void *heap, void *memory);

void g1_recon_k_free(void *allocation)
{
    unsigned char *header;

    if (allocation == 0) {
        return;
    }
    header = (unsigned char *)allocation - 4;
    k_heap_free(*(void **)header, header);
}
