#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   0x00066630       => struct g1_layout_nrfx_qspi_write_region__global_1561    [global_1561; library]
 *   0x0006661c       => struct g1_layout_nrfx_qspi_cb__global_1562              [global_1562; library]
 * Raw function identity: 0x00085200.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00085200 @ 0x00085200
 * public-name: nrfx_qspi_write
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   qspi_xfer                                <= FUN_00066524 @ 0x00066524
 *   nrfx_qspi_write                          <= FUN_00085200 @ 0x00085200
 */
/* Reconstructed FUN_00085200 @ 0x85200.
 * Complete six-byte tail-call wrapper; 0x85206 starts the next function. */
extern int qspi_xfer(int, int, int, int);
int nrfx_qspi_write(int param_1, int param_2, int param_3) {
  return qspi_xfer(param_1, param_2, param_3, 2);
}
