/* named: projector_bus_lock */
/* globals referenced:
//   0x2000a060  g_projector_bus_lock         
*/
/* Reconstructed projector_bus_lock @ 0x47698  (parity: 300/300 trials, PROVEN) */

extern void k_mutex_lock(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3);
void projector_bus_lock(unsigned int param_1, unsigned int param_2)
{
  k_mutex_lock(0x2000a060UL, param_2, param_1, param_2);
}

