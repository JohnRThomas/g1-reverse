#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00077c78 @ 0x00077c78
 * public-name: vsprintf_impl
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   _vsprintf_r                              <= FUN_00077c4c @ 0x00077c4c
 *   vsprintf_impl                            <= FUN_00077c78 @ 0x00077c78
 * address symbols (name @ address):
 *   g_libc_heap_ctrl                         @ 0x20002d20
 */
/* Reconstructed FUN_00077c78 @ 0x77c78  (parity: 300/300 trials, PROVEN) */

extern void _vsprintf_r(unsigned int, unsigned int, unsigned int, unsigned int);

void vsprintf_impl(unsigned char *param_1, unsigned int param_2, unsigned int param_3)
{
    unsigned int v = *(volatile unsigned int*)((unsigned long)&g_libc_heap_ctrl) /*=0x20002d20*/;
    _vsprintf_r(v, (unsigned int)param_1, param_2, param_3);
}
