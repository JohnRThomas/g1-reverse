/* named: ancs_cancel_timers */
/* globals referenced:
//   0x20006ab4  g_gatt_discovery_flags       
*/
/* Reconstructed ancs_cancel_timers @ 0x18ab0  (parity: 300/300 trials, PROVEN) */

extern void atomic_and(unsigned int a0, unsigned int a1);

void ancs_cancel_timers(void)
{
  atomic_and(0x20006ab4, 0xfffffffe);
  atomic_and(0x20006ab4, 0xfffffffd);
  atomic_and(0x20006ab4, 0xfffffffb);
}

