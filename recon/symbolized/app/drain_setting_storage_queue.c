#include "g1_app_symbols.h"
#include <zephyr/sys_clock.h>
/* readable reconstruction; identity: FUN_00023acc @ 0x00023acc
 * public-name: drain_setting_storage_queue
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   drain_setting_storage_queue              <= FUN_00023acc @ 0x00023acc
 *   k_msgq_get                               <= FUN_00072240 @ 0x00072240
 * address symbols (name @ address):
 *   g_flash_store_cmd_msgq                   @ 0x20003994
 */
/* Reconstructed FUN_00023acc @ 0x23acc  (parity: 300/300 trials, PROVEN) */

extern int k_msgq_get(struct k_msgq *, void *, k_timeout_t);

unsigned int drain_setting_storage_queue(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7, int count)
{
  unsigned int uVar1;
  unsigned int uVar2;
  unsigned int stk[3];

  uVar1 = ((unsigned long)&g_flash_store_cmd_msgq) /*=0x20003994*/;
  uVar2 = 0;
  stk[0] = param_1;
  stk[1] = param_2;
  stk[2] = param_3;
  for (; count > 0; count--) {
    uVar2 = k_msgq_get(uVar1, stk, (k_timeout_t){ .ticks = 0LL });
  }
  return uVar2;
}
