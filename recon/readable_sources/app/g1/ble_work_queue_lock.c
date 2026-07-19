#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00019b38 @ 0x00019b38
 * public-name: ble_work_queue_lock
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ble_work_queue_lock                      <= FUN_00019b38 @ 0x00019b38
 *   k_mutex_lock                             <= FUN_000723b8 @ 0x000723b8
 * address symbols (name @ address):
 *   g_ble_work_queue                         @ 0x20007574
 */
/* Reconstructed FUN_00019b38 @ 0x19b38  (parity: 300/300 trials, PROVEN) */

extern void k_mutex_lock(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3);
void ble_work_queue_lock(unsigned int param_1, unsigned int param_2)
{
  k_mutex_lock(((unsigned long)&g_ble_work_queue) /*=0x20007574*/, param_2, param_1, param_2);
}
