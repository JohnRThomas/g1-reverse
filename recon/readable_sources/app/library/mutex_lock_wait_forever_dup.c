#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000859b6 @ 0x000859b6
 * public-name: mutex_lock_wait_forever_dup
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_impl_k_sem_take                        <= FUN_00072908 @ 0x00072908
 *   mutex_lock_wait_forever_dup              <= FUN_000859b6 @ 0x000859b6
 */
/* Reconstructed FUN_000859b6 @ 0x859b6  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void z_impl_k_sem_take(unsigned int,unsigned int,unsigned int,unsigned int);
void mutex_lock_wait_forever_dup(unsigned int param_1,unsigned int param_2)
{
  z_impl_k_sem_take(param_1,param_2,0xffffffff,0xffffffff);
  return;
}
