#include "g1_app_symbols.h"
/* named: discovery_service_not_found_cb_ancs */
/* globals referenced:
//   0x20006ab4  g_gatt_discovery_flags       
*/
/* Reconstructed discovery_service_not_found_cb_ancs @ 0x18978  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned int);
extern void atomic_and(void *, unsigned int);
extern void gatt_discover(unsigned int, unsigned int);

void discovery_service_not_found_cb_ancs(unsigned int param_1)
{
  DEBUG_PRINT("ANCS could not be found during the discovery\n" /*=0x9a7f2*/);
  atomic_and((void*)((uintptr_t)&g_gatt_discovery_flags) /*=0x20006ab4*/,0xfffffffeUL);
  gatt_discover(param_1,1);
  return;
}

