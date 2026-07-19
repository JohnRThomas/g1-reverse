#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_flash_area__param_0319                 [param_0319; library]
 * Raw function identity: 0x00084e58.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00084e58 @ 0x00084e58
 * public-name: nvs_flush_close_ate
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   flash_write_close_ate_marker             <= FUN_00084e44 @ 0x00084e44
 *   nvs_flush_close_ate                      <= FUN_00084e58 @ 0x00084e58
 */
/* Reconstructed FUN_00084e58 @ 0x84e58 */
#include <stdint.h>

extern void flash_write_close_ate_marker(uintptr_t, uint32_t, uint32_t);

void nvs_flush_close_ate(uintptr_t peripheral)
{
  uint32_t buffer =
      (*(volatile uint32_t *)(peripheral + 8) - 0x18u) & ~7u;
  flash_write_close_ate_marker(peripheral, buffer, 1);
}
