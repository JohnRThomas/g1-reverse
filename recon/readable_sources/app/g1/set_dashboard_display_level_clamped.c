#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00048b44 @ 0x00048b44
 * public-name: set_dashboard_display_level_clamped
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   set_dashboard_display_level_clamped      <= FUN_00048b44 @ 0x00048b44
 * address symbols (name @ address):
 *   g_dashboard_display_level                @ 0x20002544
 */
/* Reconstructed FUN_00048b44 @ 0x48b44  (parity: 300/300 trials, PROVEN) */

unsigned int set_dashboard_display_level_clamped(int param_1)
{
    if (param_1 >= 0x7d) {
        param_1 = 0x7d;
    }
    if (param_1 < 0x21) {
        param_1 = 0x21;
    }
    *(volatile unsigned int*)((unsigned long)&g_dashboard_display_level) /*=0x20002544*/ = param_1;
    return 0;
}
