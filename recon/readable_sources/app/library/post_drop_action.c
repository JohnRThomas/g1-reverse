#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_mpsc_pbuf_buffer__param_0133           [param_0133; library]
 * Raw function identity: 0x0007e4bc.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0007e4bc @ 0x0007e4bc
 * public-name: post_drop_action
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   idx_inc                                  <= FUN_0007e35c @ 0x0007e35c
 *   post_drop_action                         <= FUN_0007e4bc @ 0x0007e4bc
 */
/* Reconstructed FUN_0007e4bc @ 0x7e4bc  (parity: 300/300 trials, PROVEN) */

extern long long idx_inc();

void post_drop_action(int *param_1, unsigned int param_2, int param_3)
{
  long long uVar2;
  int iVar1;
  uVar2 = idx_inc();
  iVar1 = (int)(uVar2 >> 32);
  if (*param_1 == (int)uVar2) {
    *param_1 = iVar1;
    param_1[4] = param_1[4] & 0xfffffff7;
  } else {
    *(unsigned int *)(param_1[8] + iVar1 * 4) = (param_3 << 2) | 2;
    iVar1 = (int)idx_inc((int)param_1, param_1[1], param_3);
    param_1[1] = iVar1;
  }
}
