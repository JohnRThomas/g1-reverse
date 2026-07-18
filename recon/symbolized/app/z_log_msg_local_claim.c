#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0004d56c @ 0x0004d56c
 * public-name: z_log_msg_local_claim
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_log_msg_local_claim                    <= FUN_0004d56c @ 0x0004d56c
 * address symbols (name @ address):
 *   g_log_msg_mpsc_buffer                    @ 0x20003648
 */
/* Reconstructed FUN_0004d56c @ 0x4d56c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
/* mpsc_pbuf_claim <= FUN_0004beb8 @ 0x0004beb8 */
extern unsigned mpsc_pbuf_claim(void *);
unsigned z_log_msg_local_claim(void)
{
  return mpsc_pbuf_claim((void *)((unsigned long)&g_log_msg_mpsc_buffer) /*=0x20003648*/);
}
