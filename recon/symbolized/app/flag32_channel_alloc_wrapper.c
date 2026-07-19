#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0006540c @ 0x0006540c
 * public-name: flag32_channel_alloc_wrapper
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   nrfx_flag32_alloc                        <= FUN_00064eb8 @ 0x00064eb8
 *   flag32_channel_alloc_wrapper             <= FUN_0006540c @ 0x0006540c
 * address symbols (name @ address):
 *   g_flag32_channel_alloc_mask              @ 0x20002bbc
 */
/* Reconstructed FUN_0006540c @ 0x6540c  (parity: 300/300 trials, PROVEN) */

extern void nrfx_flag32_alloc(unsigned int, unsigned int);
void flag32_channel_alloc_wrapper(unsigned int param_1)
{
    nrfx_flag32_alloc(((unsigned long)&g_flag32_channel_alloc_mask) /*=0x20002bbc*/, param_1);
}
