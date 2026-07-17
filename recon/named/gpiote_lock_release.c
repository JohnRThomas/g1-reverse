/* readable reconstruction; identity: FUN_000659cc @ 0x000659cc
 * public-name: gpiote_lock_release
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   nrfx_flag32_free                         <= FUN_00064ef8 @ 0x00064ef8
 *   gpiote_lock_release                      <= FUN_000659cc @ 0x000659cc
 * address symbols (name @ address):
 *   g_gpiote_lock                            @ 0x20002c30
 */
/* Reconstructed FUN_000659cc @ 0x659cc  (parity: 300/300 trials, PROVEN) */

extern void nrfx_flag32_free(unsigned int, unsigned int);
void gpiote_lock_release(unsigned int param_1)
{
    nrfx_flag32_free(0x20002c30UL, param_1);
}
