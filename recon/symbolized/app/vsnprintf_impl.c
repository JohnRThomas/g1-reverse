#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00077c30 @ 0x00077c30
 * public-name: vsnprintf_impl
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   vsnprintf_impl                           <= FUN_00077c30 @ 0x00077c30
 * address symbols (name @ address):
 *   g_libc_heap_ctrl                         @ 0x20002d20
 */
/* Reconstructed FUN_00077c30 @ 0x77c30  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int FUN_0008712e(int a, int b, int c, int d, int e, int f, int g);
void vsnprintf_impl(int param_1, int param_2, int param_3, int param_4) {
    FUN_0008712e(*(volatile int*)((unsigned long)&g_libc_heap_ctrl) /*=0x20002d20*/, param_1, param_2, param_3, param_4, param_2, param_3);
}
