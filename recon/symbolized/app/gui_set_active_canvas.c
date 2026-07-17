#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000431b4 @ 0x000431b4
 * public-name: gui_set_active_canvas
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gui_set_active_canvas                    <= FUN_000431b4 @ 0x000431b4
 * address symbols (name @ address):
 *   g_gui_active_canvas                      @ 0x2000a034
 */
/* Reconstructed FUN_000431b4 @ 0x431b4  (parity: 300/300 trials, PROVEN) */

unsigned int gui_set_active_canvas(unsigned int param_1)
{
    *(volatile unsigned int*)((unsigned long)&g_gui_active_canvas) /*=0x2000a034*/ = param_1;
    return 0;
}
