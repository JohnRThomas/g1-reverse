#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_smp_reassembly_ctx__param_0558         [param_0558; library]
 * Raw function identity: 0x00080b28.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00080b28 @ 0x00080b28
 * public-name: smp_reassembly_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   smp_reassembly_init                      <= FUN_00080b28 @ 0x00080b28
 */
/* Reconstructed FUN_00080b28 @ 0x80b28  (parity: 300/300 trials, PROVEN) */

void smp_reassembly_init(int param_1)
{
  *(volatile unsigned int *)(param_1 + 0x40) = 0;
  *(volatile unsigned short *)(param_1 + 0x44) = 0;
}
