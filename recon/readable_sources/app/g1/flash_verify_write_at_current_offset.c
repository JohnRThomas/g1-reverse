#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_flash_area__param_0319                 [param_0319; library]
 * Raw function identity: 0x00084e66.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00084e66 @ 0x00084e66
 * public-name: flash_verify_write_at_current_offset
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   flash_write_byte_and_verify              <= FUN_00084db2 @ 0x00084db2
 *   flash_verify_write_at_current_offset     <= FUN_00084e66 @ 0x00084e66
 */
/* Reconstructed FUN_00084e66 @ 0x84e66  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void flash_write_byte_and_verify(int,unsigned int,unsigned int);
void flash_verify_write_at_current_offset(int param_1,unsigned int param_2)
{
  flash_write_byte_and_verify(param_1,param_2,*(volatile uint32_t*)(param_1 + 8) - 0x18U & 0xfffffff8);
  return;
}
