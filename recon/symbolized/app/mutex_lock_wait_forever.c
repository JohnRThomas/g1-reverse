#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0008583a @ 0x0008583a
 * public-name: mutex_lock_wait_forever
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   mutex_lock_syscall_handler               <= FUN_00072908 @ 0x00072908
 *   mutex_lock_wait_forever                  <= FUN_0008583a @ 0x0008583a
 */
/* Reconstructed FUN_0008583a @ 0x8583a  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void mutex_lock_syscall_handler(unsigned int,unsigned int,unsigned int,unsigned int);
void mutex_lock_wait_forever(unsigned int param_1,unsigned int param_2)
{
  mutex_lock_syscall_handler(param_1,param_2,0xffffffff,0xffffffff);
  return;
}
