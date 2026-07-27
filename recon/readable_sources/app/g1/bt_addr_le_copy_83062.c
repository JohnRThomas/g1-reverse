#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_bt_addr_le_t__param_0636               [param_0636; library]
 *   param_2          => struct g1_layout_bt_addr_le_t__param_0637               [param_0637; library]
 * Raw function identity: 0x00083062.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00083062 @ 0x00083062
 * public-name: bt_addr_le_copy_83062
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_addr_le_copy_83062                    <= FUN_00083062 @ 0x00083062
 */
/* Reconstructed FUN_00083062 @ 0x83062  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
void bt_addr_le_copy_83062(unsigned int*param_1, unsigned int*param_2) {
  *param_1 = *param_2;
  *(uint16_t*)((char*)param_1 + 4) = *(uint16_t*)((char*)param_2 + 4);
  *(uint8_t*)((char*)param_1 + 6) = *(uint8_t*)((char*)param_2 + 6);
  return;
}
