#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007d3dc @ 0x0007d3dc
 * public-name: gui_utf_adv_draw_configure
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   display_mode_globals_configure           <= FUN_0004372c @ 0x0004372c
 *   gui_utf_adv_draw_configure               <= FUN_0007d3dc @ 0x0007d3dc
 */
/* Full reconstruction FUN_0007d3dc @ 0x7d3dc (exact extent 18 bytes). */

extern unsigned int display_mode_globals_configure(unsigned int mode);

unsigned int gui_utf_adv_draw_configure(void)
{
    return display_mode_globals_configure(8);
}
