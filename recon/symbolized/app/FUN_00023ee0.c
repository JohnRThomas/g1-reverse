#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00023ee0 @ 0x00023ee0
 * public-name: FUN_00023ee0
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_ui_mode_flag                           @ 0x20018462
 */
/* Reconstructed FUN_00023ee0 @ 0x23ee0  (parity: 300/300 trials, PROVEN) */

unsigned char FUN_00023ee0(void) {
    return *(volatile unsigned char*)(((unsigned long)&g_ui_mode_flag) /*=0x20018462*/ + 1);
}
