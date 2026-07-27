#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0008131c @ 0x0008131c
 * public-name: bt_le_adv_set_enable_legacy_veneer
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_le_adv_set_enable_legacy_veneer       <= FUN_0008131c @ 0x0008131c
 */
/* Reconstructed FUN_0008131c @ 0x0008131c.
 * Exact branch veneer to bt_le_adv_set_enable_legacy @ 0x000812d2.
 */
#include <stdint.h>
extern int bt_le_adv_set_enable_legacy(void *, unsigned int);
int bt_le_adv_set_enable_legacy_veneer(void *advertising_set, uint32_t enable)
{
    return bt_le_adv_set_enable_legacy(advertising_set, enable);
}
