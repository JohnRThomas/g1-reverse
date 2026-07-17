/* readable reconstruction; identity: FUN_0003443c @ 0x0003443c
 * public-name: FUN_0003443c
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   msg_content_decrement_timer              <= FUN_0003441c @ 0x0003441c
 * address symbols (name @ address):
 *   g_message_pending_state                  @ 0x2001a229
 */
/* Reconstructed FUN_0003443c @ 0x3443c  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void msg_content_decrement_timer(void);
void FUN_0003443c(int param_1)
{
  *(volatile uint8_t*)0x2001a229UL = (uint8_t)param_1;
  if (param_1 == 0) {
    msg_content_decrement_timer();
    return;
  }
  return;
}
