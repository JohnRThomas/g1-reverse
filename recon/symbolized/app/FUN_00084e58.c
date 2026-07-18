#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00084e58 @ 0x00084e58
 * public-name: FUN_00084e58
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   flash_write_close_ate_marker             <= FUN_00084e44 @ 0x00084e44
 */
/* Reconstructed FUN_00084e58 @ 0x84e58 */
#include <stdint.h>

extern void flash_write_close_ate_marker(uintptr_t, uint32_t, uint32_t);

void FUN_00084e58(uintptr_t peripheral)
{
  uint32_t buffer =
      (*(volatile uint32_t *)(peripheral + 8) - 0x18u) & ~7u;
  flash_write_close_ate_marker(peripheral, buffer, 1);
}
