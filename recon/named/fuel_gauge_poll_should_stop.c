/* named: fuel_gauge_poll_should_stop */
/* globals referenced:
//   0x20019dae  g_fuel_gauge_poll_stop_flag  
*/
/* Reconstructed fuel_gauge_poll_should_stop @ 0x30cac  (parity: 300/300 trials, PROVEN) */

unsigned char fuel_gauge_poll_should_stop(void) {
    return *(volatile unsigned char*)0x20019daeUL;
}

