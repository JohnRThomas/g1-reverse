/* named: nfc_eeprom_comm_unlock */
/* globals referenced:
//   0x20019dae  g_fuel_gauge_poll_stop_flag  
*/
/* Reconstructed nfc_eeprom_comm_unlock @ 0x30cc4  (parity: 300/300 trials, PROVEN) */

void nfc_eeprom_comm_unlock(void)
{
    *(volatile unsigned char*)0x20019daeUL = 0;
}

