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
  DEBUG_PRINT(0x0009a7f2UL);
  atomic_and((void*)0x20006ab4UL,0xfffffffeUL);
  gatt_discover(param_1,1);
  return;
}

