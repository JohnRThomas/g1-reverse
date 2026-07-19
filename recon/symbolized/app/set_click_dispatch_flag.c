#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00032fd0 @ 0x00032fd0
 * public-name: set_click_dispatch_flag
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   set_click_dispatch_flag                  <= FUN_00032fd0 @ 0x00032fd0
 * address symbols (name @ address):
 *   g_click_dispatch_flag                    @ 0x20019ef2
 */
/* Reconstructed FUN_00032fd0 @ 0x32fd0  (parity: 300/300 trials, PROVEN) */

void set_click_dispatch_flag(unsigned char param_1) {
    *(volatile unsigned char*)((unsigned long)&g_click_dispatch_flag) /*=0x20019ef2*/ = param_1;
}
