#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_flash_area__param_0319                 [param_0319; library]
 * Raw function identity: 0x00084d64.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00084d64 @ 0x00084d64
 * public-name: flash_calc_prev_ate_offset
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   flash_calc_prev_ate_offset               <= FUN_00084d64 @ 0x00084d64
 */
/* Reconstructed FUN_00084d64 @ 0x84d64  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
int flash_calc_prev_ate_offset(int param_1)
{
  return (*(volatile uint32_t*)(param_1 + 8) - 0x18U & 0xfffffff8) - 0x10;
}
