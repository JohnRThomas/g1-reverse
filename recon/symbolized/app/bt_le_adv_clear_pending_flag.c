#include "g1_app_symbols.h"
/* named: bt_le_adv_clear_pending_flag */
/* Reconstructed bt_le_adv_clear_pending_flag @ 0x81080  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void bt_le_adv_set_enable_legacy(int, uint32_t);

void bt_le_adv_clear_pending_flag(int param_1)
{
  volatile uint32_t *p = (volatile uint32_t*)(param_1 + 0x10);
  uint32_t uVar1 = *p;
  *p = uVar1 & 0xffff7fffUL;
  if ((int32_t)(uVar1 << 0x10) < 0) {
    bt_le_adv_set_enable_legacy(param_1, 1);
  }
}

