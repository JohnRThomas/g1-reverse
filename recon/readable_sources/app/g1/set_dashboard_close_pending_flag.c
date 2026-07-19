#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00036024 @ 0x00036024
 * public-name: set_dashboard_close_pending_flag
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   set_dashboard_close_pending_flag         <= FUN_00036024 @ 0x00036024
 * address symbols (name @ address):
 *   g_dashboard_close_pending                @ 0x2001b80f
 */
/* Reconstructed FUN_00036024 @ 0x36024  (parity: 300/300 trials, PROVEN) */

void set_dashboard_close_pending_flag(void)
{
    *(volatile unsigned char*)((unsigned long)&g_dashboard_close_pending) /*=0x2001b80f*/ = 1;
}
