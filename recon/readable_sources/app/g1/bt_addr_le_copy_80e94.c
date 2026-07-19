#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_bt_addr_le_t__param_0572               [param_0572; library]
 *   param_2          => struct g1_layout_bt_addr_le_t__param_0573               [param_0573; library]
 * Raw function identity: 0x00080e94.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00080e94 @ 0x00080e94
 * public-name: bt_addr_le_copy_80e94
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_addr_le_copy_80e94                    <= FUN_00080e94 @ 0x00080e94
 */
/* Reconstructed FUN_00080e94 @ 0x80e94  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
void bt_addr_le_copy_80e94(uint32_t *param_1, uint32_t *param_2)
{
  *param_1 = *param_2;
  *(uint16_t*)((char*)param_1 + 4) = *(uint16_t*)((char*)param_2 + 4);
  *(uint8_t*)((char*)param_1 + 6) = *(uint8_t*)((char*)param_2 + 6);
  return;
}
