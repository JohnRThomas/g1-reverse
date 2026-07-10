/* named: ble_work_queue_lock */
/* globals referenced:
//   0x20007574  g_ble_work_queue             
*/
/* Reconstructed ble_work_queue_lock @ 0x19b38  (parity: 300/300 trials, PROVEN) */

extern void k_mutex_lock(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3);
void ble_work_queue_lock(unsigned int param_1, unsigned int param_2)
{
  k_mutex_lock(0x20007574UL, param_2, param_1, param_2);
}

