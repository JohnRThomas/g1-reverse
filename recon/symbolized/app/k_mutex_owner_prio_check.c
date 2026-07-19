#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000864b2 @ 0x000864b2
 * public-name: k_mutex_owner_prio_check
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_sched_set_prio_and_requeue             <= FUN_00074060 @ 0x00074060
 *   k_mutex_owner_prio_check                 <= FUN_000864b2 @ 0x000864b2
 */
/* Reconstructed FUN_000864b2 @ 0x864b2  (parity: 300/300 trials, PROVEN) */

extern unsigned int z_sched_set_prio_and_requeue(void);
unsigned int k_mutex_owner_prio_check(int param_1,int param_2)
{
  if (*(signed char *)(param_1 + 0xe) != param_2) {
    return z_sched_set_prio_and_requeue();
  }
  return 0;
}
