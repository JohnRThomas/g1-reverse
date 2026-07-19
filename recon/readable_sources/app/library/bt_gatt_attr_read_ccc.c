#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   local_12         => struct g1_layout_bt_gatt_attr_read_ccc_locals__stack_1532 [stack_1532; G1-original]
 * Raw function identity: 0x0008295a.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0008295a @ 0x0008295a
 * public-name: bt_gatt_attr_read_ccc
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ccc_match_conn_cfg                       <= FUN_00059c48 @ 0x00059c48
 *   bt_gatt_attr_read                        <= FUN_00082932 @ 0x00082932
 *   bt_gatt_attr_read_ccc                    <= FUN_0008295a @ 0x0008295a
 */
/* Reconstructed FUN_0008295a @ 0x8295a  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern uint32_t ccc_match_conn_cfg(uint32_t, uint32_t);
extern void bt_gatt_attr_read(uint32_t, uint32_t, uint16_t, void*, uint32_t);

void bt_gatt_attr_read_ccc(uint32_t param_1, int param_2, uint32_t param_3, uint32_t param_4, uint16_t param_5)
{
  uint32_t uVar1;
  uint16_t local_12[3];
  uVar1 = ccc_match_conn_cfg(param_1, *(uint32_t*)(param_2+0xc));
  if (uVar1 != 0) {
    uVar1 = *(uint16_t*)(uVar1+8);
  }
  local_12[0] = (uint16_t)uVar1;
  bt_gatt_attr_read(param_3, param_4, param_5, local_12, 2);
}
