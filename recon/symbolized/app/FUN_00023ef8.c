#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00023ef8 @ 0x00023ef8
 * public-name: FUN_00023ef8
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_flash_store_cmd_msgq                   @ 0x20003994
 */
/* Reconstructed FUN_00023ef8 @ 0x23ef8  (parity: 300/300 trials, PROVEN) */

unsigned int FUN_00023ef8(void) {
    return *(volatile unsigned int*)(((unsigned long)&g_flash_store_cmd_msgq) /*=0x20003994*/ + 0x24);
}
