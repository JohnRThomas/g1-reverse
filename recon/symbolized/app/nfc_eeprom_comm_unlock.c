#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00030cc4 @ 0x00030cc4
 * public-name: nfc_eeprom_comm_unlock
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   nfc_eeprom_comm_unlock                   <= FUN_00030cc4 @ 0x00030cc4
 * address symbols (name @ address):
 *   g_fuel_gauge_poll_stop_flag              @ 0x20019dae
 */
/* Reconstructed FUN_00030cc4 @ 0x30cc4  (parity: 300/300 trials, PROVEN) */

void nfc_eeprom_comm_unlock(void)
{
    *(volatile unsigned char*)((unsigned long)&g_fuel_gauge_poll_stop_flag) /*=0x20019dae*/ = 0;
}
