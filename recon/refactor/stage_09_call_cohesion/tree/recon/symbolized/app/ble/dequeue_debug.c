#include "g1_app_symbols.h"
#include <zephyr/sys_clock.h>
/* readable reconstruction; identity: FUN_00019c44 @ 0x00019c44
 * public-name: dequeue_debug
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   dequeue_debug                            <= FUN_00019c44 @ 0x00019c44
 *   k_msgq_get                               <= FUN_00072240 @ 0x00072240
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 * address symbols (name @ address):
 *   g_debug_msg_pipe                         @ 0x2000751c
 */
/* Reconstructed FUN_00019c44 @ 0x19c44  (parity: 300/300 trials, PROVEN) */

extern int k_msgq_get(struct k_msgq *, void *, k_timeout_t);
extern void memcpy(int, int, int);

int dequeue_debug(unsigned int param_1)
{
  int iVar1;
  unsigned char auStack_d8[204];
  iVar1 = k_msgq_get(((unsigned long)&g_debug_msg_pipe) /*=0x2000751c*/, auStack_d8, (k_timeout_t){ .ticks = 0LL });
  if (iVar1 == 0) {
    memcpy(param_1, auStack_d8, 200);
  }
  return iVar1;
}
