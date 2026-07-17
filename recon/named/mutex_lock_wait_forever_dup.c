/* readable reconstruction; identity: FUN_000859b6 @ 0x000859b6
 * public-name: mutex_lock_wait_forever_dup
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   mutex_lock_syscall_handler               <= FUN_00072908 @ 0x00072908
 *   mutex_lock_wait_forever_dup              <= FUN_000859b6 @ 0x000859b6
 */
/* Reconstructed FUN_000859b6 @ 0x859b6  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void mutex_lock_syscall_handler(unsigned int,unsigned int,unsigned int,unsigned int);
void mutex_lock_wait_forever_dup(unsigned int param_1,unsigned int param_2)
{
  mutex_lock_syscall_handler(param_1,param_2,0xffffffff,0xffffffff);
  return;
}
