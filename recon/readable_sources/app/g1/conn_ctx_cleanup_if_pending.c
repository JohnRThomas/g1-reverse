#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00081720 @ 0x00081720
 * public-name: conn_ctx_cleanup_if_pending
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   k_work_reschedule                        <= FUN_0007350c @ 0x0007350c
 *   atomic_get_word                          <= FUN_000816a2 @ 0x000816a2
 *   conn_ctx_cleanup_if_pending              <= FUN_00081720 @ 0x00081720
 */
/* Reconstructed FUN_00081720 @ 0x81720  (parity: 300/300 trials, PROVEN) */

extern unsigned long long atomic_get_word(int a, int b);
extern void k_work_reschedule(unsigned int, unsigned int, unsigned int, unsigned int);

void conn_ctx_cleanup_if_pending(int param_1)
{
  unsigned long long uVar2 = atomic_get_word(param_1 + 0x2c, param_1);
  int iVar1 = (int)(uVar2 >> 32);
  if (((int)uVar2 != 0) && ((*(int *)(iVar1 + 0x30) != 0) || (*(int *)(iVar1 + 0x4c) != 0))) {
    k_work_reschedule(iVar1 + 0x50, iVar1, 0, 0);
  }
}
