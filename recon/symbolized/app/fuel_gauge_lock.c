#include "g1_app_symbols.h"
/* named: fuel_gauge_lock */
/* globals referenced:
//   0x20002424  g_fuel_gauge_dev             
*/
/* Reconstructed fuel_gauge_lock @ 0x330c4  (parity: 300/300 trials, PROVEN) */

extern void lock_device_mutex(void);
unsigned int fuel_gauge_lock(void) {
  if (*(volatile unsigned int*)((uintptr_t)&g_fuel_gauge_dev) /*=0x20002424*/ != 0) {
    lock_device_mutex();
  }
  return 0;
}

