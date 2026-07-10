/* Reconstructed FUN_0008295a @ 0x8295a  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern uint32_t FUN_00059c48(uint32_t, uint32_t);
extern void bt_gatt_attr_read_constprop_0(uint32_t, uint32_t, uint16_t, void*, uint32_t);

void bt_gatt_attr_read_ccc(uint32_t param_1, int param_2, uint32_t param_3, uint32_t param_4, uint16_t param_5)
{
  uint32_t uVar1;
  uint16_t local_12[3];
  uVar1 = FUN_00059c48(param_1, *(uint32_t*)(param_2+0xc));
  if (uVar1 != 0) {
    uVar1 = *(uint16_t*)(uVar1+8);
  }
  local_12[0] = (uint16_t)uVar1;
  bt_gatt_attr_read_constprop_0(param_3, param_4, param_5, local_12, 2);
}

