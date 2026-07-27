/* readable reconstruction; identity: FUN_000785c8 @ 0x000785c8
 * public-name: __malloc_unlock
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   g1_recon_retarget_lock_release_recursive <= FUN_00051134 @ 0x00051134
 *   __malloc_unlock                          <= FUN_000785c8 @ 0x000785c8
 * address symbols (name @ address):
 *   g_malloc_lock                            @ 0x200037f0
 */
/* Reconstructed FUN_000785c8 @ 0x785c8  (parity: 300/300 trials, PROVEN) */

#define g1_recon_retarget_lock_release_recursive g1_recon_retarget_lock_release_recursive
extern void g1_recon_retarget_lock_release_recursive(unsigned long); /* FUN_00051134@0x00051134 */
void __malloc_unlock(void)
{
    g1_recon_retarget_lock_release_recursive((void*)0x200037f0UL);
}
