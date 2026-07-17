#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00019bd0 @ 0x00019bd0
 * public-name: debug_log_queue_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_log_queue_init                     <= FUN_00019bd0 @ 0x00019bd0
 *   z_impl_k_msgq_alloc_init                 <= FUN_00086448 @ 0x00086448
 * address symbols (name @ address):
 *   rodata_9b331                             @ 0x0009b331
 *   rodata_9b345                             @ 0x0009b345
 *   g_debug_msg_pipe                         @ 0x2000751c
 */
/* Reconstructed FUN_00019bd0 @ 0x19bd0  (parity: 300/300 trials, PROVEN) */

extern int z_impl_k_msgq_alloc_init(void *, int, int);
extern void log_message(unsigned int);

int debug_log_queue_init(void)
{
  int iVar1;

  iVar1 = z_impl_k_msgq_alloc_init((void*)((unsigned long)&g_debug_msg_pipe) /*=0x2000751c*/, 200, 0x14);
  if (iVar1 != 0) {
    log_message(((unsigned long)&rodata_9b331) /*=0x9b331*/);
    return iVar1;
  }
  log_message(((unsigned long)&rodata_9b345) /*=0x9b345*/);
  return iVar1;
}
