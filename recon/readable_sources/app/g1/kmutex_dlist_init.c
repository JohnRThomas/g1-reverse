#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_kmutex_dlist_node__param_0728          [param_0728; G1-original]
 * Raw function identity: 0x000864c2.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_000864c2 @ 0x000864c2
 * public-name: kmutex_dlist_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   kmutex_dlist_init                        <= FUN_000864c2 @ 0x000864c2
 */
/* Reconstructed FUN_000864c2 @ 0x864c2  (parity: 300/300 trials, PROVEN) */

void kmutex_dlist_init(unsigned int *param_1) {
  param_1[0] = (unsigned int)param_1;
  param_1[1] = (unsigned int)param_1;
  param_1[2] = 0;
  param_1[3] = 0;
}
