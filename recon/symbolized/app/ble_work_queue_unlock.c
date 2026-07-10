#include "g1_app_symbols.h"
/* named: ble_work_queue_unlock */
/* globals referenced:
//   0x20007574  g_ble_work_queue             
*/
/* Reconstructed ble_work_queue_unlock @ 0x19b48  (parity: 300/300 trials, PROVEN) */

extern void k_mutex_unlock(unsigned int);
void ble_work_queue_unlock(void) {
    k_mutex_unlock(((uintptr_t)&g_ble_work_queue) /*=0x20007574*/);
}

