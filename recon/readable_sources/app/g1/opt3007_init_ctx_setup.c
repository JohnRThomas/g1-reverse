#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_opt3007_init_ctx__param_0084           [param_0084; G1-original]
 * Raw function identity: 0x0002e8fc.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0002e8fc @ 0x0002e8fc
 * public-name: opt3007_init_ctx_setup
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   opt3007_init_ctx_setup                   <= FUN_0002e8fc @ 0x0002e8fc
 * address symbols (name @ address):
 *   ADDR_opt3001_read_lux_raw_THUMB          @ 0x0002e649
 *   ADDR_opt3007_chip_init_THUMB             @ 0x0002e67d
 */
/* Reconstructed FUN_0002e8fc @ 0x2e8fc  (parity: 300/300 trials, PROVEN) */

void opt3007_init_ctx_setup(unsigned int *param_1) {
  param_1[7] = (unsigned int)param_1 - 0x430;
  param_1[0] = ADDR_opt3007_chip_init_THUMB /*=0x2e67d*/;
  param_1[3] = ADDR_opt3001_read_lux_raw_THUMB /*=0x2e649*/;
}
