#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00081080 @ 0x00081080
 * public-name: bt_le_adv_clear_pending_flag
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_le_adv_clear_pending_flag             <= FUN_00081080 @ 0x00081080
 *   bt_le_adv_set_enable_legacy_veneer       <= FUN_0008131c @ 0x0008131c
 */
/* Reconstructed FUN_00081080 @ 0x81080  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void bt_le_adv_set_enable_legacy_veneer(int, uint32_t);

void bt_le_adv_clear_pending_flag(int param_1)
{
  uint32_t *flags = (uint32_t *)(param_1 + 0x10);
  uint32_t previous = __atomic_fetch_and(flags, ~0x8000u, __ATOMIC_RELEASE);
  if ((previous & 0x8000u) != 0) {
    bt_le_adv_set_enable_legacy_veneer(param_1, 1);
  }
}
