#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_3          => struct g1_layout_opt_field1_ctx__param_0460             [param_0460; G1-original]
 *   param_1          => struct g1_layout_opt_record__param_0461                 [param_0461; G1-original]
 * Raw function identity: 0x0007c430.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0007c430 @ 0x0007c430
 * public-name: opt_field1_set
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   opt_field1_set                           <= FUN_0007c430 @ 0x0007c430
 */
/* Reconstructed FUN_0007c430 @ 0x7c430  (parity: 300/300 trials, PROVEN) */

unsigned int opt_field1_set(unsigned char *param_1, unsigned int param_2, int *param_3)
{
  if (param_1 != 0 && param_3 != 0 &&
      (*param_3 != 0 || ((char)((unsigned char*)param_3)[4] == 0))) {
    *param_1 = *param_1 | (param_2 & 7);
    param_1[1] = ((unsigned char*)param_3)[4];
    *(int *)(param_1 + 4) = *param_3;
    return 0;
  }
  return 7;
}
