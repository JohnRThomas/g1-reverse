#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   local_70         => struct g1_layout_vsprintf_fmt_state_tmp__stack_1428     [stack_1428; G1-original]
 * Raw function identity: 0x00077c78.  See ../include/g1_recovered_layouts.h. */
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
