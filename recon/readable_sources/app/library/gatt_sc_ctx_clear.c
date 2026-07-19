#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_gatt_sc_ctx__param_0627                [param_0627; library]
 * Raw function identity: 0x00082928.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00082928 @ 0x00082928
 * public-name: gatt_sc_ctx_clear
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gatt_sc_ctx_clear                        <= FUN_00082928 @ 0x00082928
 */
/* Reconstructed FUN_00082928 @ 0x82928  (parity: 300/300 trials, PROVEN) */

void gatt_sc_ctx_clear(unsigned int *param_1)
{
  param_1[0] = 0;
  param_1[1] = 0;
  param_1[2] = 0;
}
