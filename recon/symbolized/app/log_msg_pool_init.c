#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0004d508 @ 0x0004d508
 * public-name: log_msg_pool_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   mpsc_pbuf_init                           <= FUN_0004bc28 @ 0x0004bc28
 *   log_msg_pool_init                        <= FUN_0004d508 @ 0x0004d508
 * address symbols (name @ address):
 *   rodata_8aca0                             @ 0x0008aca0
 *   g_log_msg_mpsc_buffer                    @ 0x20003648
 *   g_log_msg_pool_ptr                       @ 0x2000a0cc
 */
/* Reconstructed FUN_0004d508 @ 0x4d508  (parity: 300/300 trials, PROVEN) */

extern void mpsc_pbuf_init(unsigned int, unsigned int);
void log_msg_pool_init(void)
{
  mpsc_pbuf_init(((unsigned long)&g_log_msg_mpsc_buffer) /*=0x20003648*/, ((unsigned long)&rodata_8aca0) /*=0x8aca0*/);
  *(volatile unsigned int *)((unsigned long)&g_log_msg_pool_ptr) /*=0x2000a0cc*/ = ((unsigned long)&g_log_msg_mpsc_buffer) /*=0x20003648*/;
}
