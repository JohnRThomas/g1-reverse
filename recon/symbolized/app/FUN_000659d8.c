#include "g1_app_symbols.h"
/* named: FUN_000659d8 */
/* globals referenced:
//   0x20002c30  g_gpiote_lock                
*/
/* Reconstructed FUN_000659d8 @ 0x659d8  (parity: 300/300 trials, PROVEN) */

extern void nrfx_flag32_alloc(unsigned int, unsigned int);
void FUN_000659d8(unsigned int param_1)
{
    nrfx_flag32_alloc(((uintptr_t)&g_gpiote_lock) /*=0x20002c30*/, param_1);
}

