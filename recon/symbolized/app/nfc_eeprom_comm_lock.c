#include "g1_app_symbols.h"
/* named: nfc_eeprom_comm_lock */
/* globals referenced:
//   0x20019dae  g_fuel_gauge_poll_stop_flag  
*/
/* Reconstructed nfc_eeprom_comm_lock @ 0x30cb8  (parity: 300/300 trials, PROVEN) */

void nfc_eeprom_comm_lock(void)
{
    *(volatile unsigned char*)((uintptr_t)&g_fuel_gauge_poll_stop_flag) /*=0x20019dae*/ = 1;
}

