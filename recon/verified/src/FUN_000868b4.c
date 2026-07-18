/* Reconstructed g1_recon_k_free @ 0x000868b4.
 * Raw backmap: FUN_000868b4@0x000868b4. */

#define k_heap_free FUN_00071b2c
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
