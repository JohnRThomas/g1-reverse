#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007d874 @ 0x0007d874
 * public-name: projector_reflash_and_release
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   display_reflash                          <= FUN_0004967c @ 0x0004967c
 *   mutex_unlock_syscall_handler             <= FUN_000745c8 @ 0x000745c8
 *   projector_reflash_and_release            <= FUN_0007d874 @ 0x0007d874
 */
/* Reconstructed FUN_0007d874 @ 0x7d874  (parity: 300/300 trials, PROVEN) */

extern void display_reflash(void*,unsigned int,unsigned int,unsigned int,unsigned int);
extern void mutex_unlock_syscall_handler(void);
unsigned int projector_reflash_and_release(unsigned int param_1,unsigned int param_2,unsigned int param_3)
{
  unsigned char buf[2];
  buf[0] = 1;
  buf[1] = (unsigned char)param_1;
  display_reflash(buf,2,param_3,1,param_1);
  mutex_unlock_syscall_handler();
  return 0;
}
