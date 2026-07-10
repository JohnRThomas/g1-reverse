#include "g1_app_symbols.h"
/* named: fuel_gauge_unlock */
/* globals referenced:
//   0x20002424  g_fuel_gauge_dev             
*/
/* Reconstructed fuel_gauge_unlock @ 0x330d8  (parity: 300/300 trials, PROVEN) */

extern void unlock_device_mutex(void);
unsigned int fuel_gauge_unlock(void) {
  if (*(volatile unsigned int*)((uintptr_t)&g_fuel_gauge_dev) /*=0x20002424*/ != 0) {
    unlock_device_mutex();
  }
  return 0;
}

