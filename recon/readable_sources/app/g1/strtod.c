#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   local_7c         => struct g1_layout_strtod_bigint_scratch__stack_1425      [stack_1425; library]
 *   local_30         => struct g1_layout_strtod_scratch__stack_1426             [stack_1426; G1-original]
 *   local_3c         => struct g1_layout_strtod_locals__stack_1427              [stack_1427; G1-original]
 * Raw function identity: 0x00077a10.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00077a10 @ 0x00077a10
 * public-name: strtod
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   strtod                                   <= FUN_00077a10 @ 0x00077a10
 * address symbols (name @ address):
 *   g_libc_heap_ctrl                         @ 0x20002d20
 *   g_20002d84                               @ 0x20002d84
 */
/* FUN_00077a10 @ 0x00077a10; raw FUN_00077a10.
 * Newlib-nano strtod wrapper; noncontiguous raw target 0x00013f58 is
 * _strtod_l, retained here as an ordinary named SDK call for linking. */

typedef unsigned char byte;
typedef unsigned long long u64;
extern u64 _strtod_l(void *reent, byte *s, void *endptr, void *locale);
u64 strtod(byte *param_1, void *param_2) {
    void *r = *(void **)((unsigned long)&g_libc_heap_ctrl) /*=0x20002d20*/;
    return _strtod_l(r, param_1, param_2, (void *)((unsigned long)&g_20002d84) /*=0x20002d84*/); /*=0x00013f58*/
}
