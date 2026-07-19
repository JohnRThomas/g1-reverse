/* readable reconstruction; identity: FUN_000659d8 @ 0x000659d8
 * public-name: gpiote_channel_flag_alloc
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   nrfx_flag32_alloc                        <= FUN_00064eb8 @ 0x00064eb8
 *   gpiote_channel_flag_alloc                <= FUN_000659d8 @ 0x000659d8
 * address symbols (name @ address):
 *   g_gpiote_lock                            @ 0x20002c30
 */
/* Reconstructed FUN_000659d8 @ 0x659d8  (parity: 300/300 trials, PROVEN) */

extern void nrfx_flag32_alloc(unsigned int, unsigned int);
void gpiote_channel_flag_alloc(unsigned int param_1)
{
    nrfx_flag32_alloc(0x20002c30UL, param_1);
}
