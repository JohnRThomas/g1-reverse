/* named: nfc_eeprom_comm_lock */
/* globals referenced:
//   0x20019dae  g_fuel_gauge_poll_stop_flag  
*/
/* Reconstructed nfc_eeprom_comm_lock @ 0x30cb8  (parity: 300/300 trials, PROVEN) */

void nfc_eeprom_comm_lock(void)
{
    *(volatile unsigned char*)0x20019daeUL = 1;
}

