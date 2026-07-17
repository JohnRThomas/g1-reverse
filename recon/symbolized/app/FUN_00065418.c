#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00065418 @ 0x00065418
 * public-name: FUN_00065418
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   nrfx_flag32_free                         <= FUN_00064ef8 @ 0x00064ef8
 * address symbols (name @ address):
 *   g_flag32_channel_alloc_mask              @ 0x20002bbc
 *   REG_50017508                             @ 0x50017508
 */
/* Reconstructed FUN_00065418 @ 0x65418  (parity: 300/300 trials, PROVEN) */

extern void nrfx_flag32_free(unsigned int a, unsigned int b);

void FUN_00065418(unsigned int param_1)
{
    *(volatile unsigned int*)REG_50017508 /*=0x50017508*/ = 1u << (param_1 & 0xff);
    nrfx_flag32_free(((unsigned long)&g_flag32_channel_alloc_mask) /*=0x20002bbc*/, param_1);
}
