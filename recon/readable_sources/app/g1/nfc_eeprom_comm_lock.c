#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00030cb8 @ 0x00030cb8
 * public-name: nfc_eeprom_comm_lock
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   nfc_eeprom_comm_lock                     <= FUN_00030cb8 @ 0x00030cb8
 * address symbols (name @ address):
 *   g_fuel_gauge_poll_stop_flag              @ 0x20019dae
 */
/* Reconstructed FUN_00030cb8 @ 0x30cb8  (parity: 300/300 trials, PROVEN) */

void nfc_eeprom_comm_lock(void)
{
    *(volatile unsigned char*)((unsigned long)&g_fuel_gauge_poll_stop_flag) /*=0x20019dae*/ = 1;
}
