#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_fs_usage_stats__param_0501             [param_0501; library]
 * Raw function identity: 0x0007e314.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0007e314 @ 0x0007e314
 * public-name: free_space
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   free_space                               <= FUN_0007e314 @ 0x0007e314
 */
/* Reconstructed FUN_0007e314 @ 0x7e314  (parity: 300/300 trials, PROVEN) */

int free_space(unsigned int *param_1, int *param_2)
{
  int iVar1; unsigned int uVar2; int iVar3;
  if ((param_1[4] & 8) == 0) {
    uVar2 = param_1[0];
    if (uVar2 < param_1[3]) { iVar1=0; iVar3 = (int)(param_1[3]-uVar2); }
    else { iVar1=1; iVar3 = (int)(param_1[9]-uVar2); }
  } else { iVar1=0; iVar3=0; }
  *param_2 = iVar3;
  return iVar1;
}
