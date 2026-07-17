#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0004b1cc @ 0x0004b1cc
 * public-name: vprintf
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_cbvprintf_impl                         <= FUN_000113a8 @ 0x000113a8
 *   vprintf                                  <= FUN_0004b1cc @ 0x0004b1cc
 * address symbols (name @ address):
 *   rodata_4b1b5                             @ 0x0004b1b5
 */
/* Reconstructed FUN_0004b1cc @ 0x4b1cc  (parity: 300/300 trials, PROVEN) */

extern void z_cbvprintf_impl(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e, unsigned int f, unsigned int g);

void vprintf(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
    z_cbvprintf_impl(((unsigned long)&rodata_4b1b5) /*=0x4b1b5*/, 0, param_1, param_2, 0, param_2, param_3);
}
