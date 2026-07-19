#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_mpsc_pbuf_buffer__param_0133           [param_0133; library]
 * Raw function identity: 0x0007e4f2.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0007e4f2 @ 0x0007e4f2
 * public-name: max_utilization_update
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_usage                                <= FUN_0007e33a @ 0x0007e33a
 *   max_utilization_update                   <= FUN_0007e4f2 @ 0x0007e4f2
 */
/* Reconstructed FUN_0007e4f2 @ 0x7e4f2  (parity: 300/300 trials, PROVEN) */

extern unsigned int get_usage(void);
void max_utilization_update(int param_1)
{
  unsigned int uVar1;
  unsigned int uVar2;
  if ((*(volatile int *)(param_1 + 0x10) << 0x1d) < 0) {
    uVar2 = *(volatile unsigned int *)(param_1 + 0x28);
    uVar1 = get_usage();
    if (uVar1 <= uVar2) {
      *(volatile unsigned int *)(param_1 + 0x28) = uVar2;
    }
    if (uVar1 > uVar2) {
      *(volatile unsigned int *)(param_1 + 0x28) = uVar1;
    }
  }
}
