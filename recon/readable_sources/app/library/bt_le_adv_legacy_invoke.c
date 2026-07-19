#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00055710 @ 0x00055710
 * public-name: bt_le_adv_legacy_invoke
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_le_adv_legacy_invoke                  <= FUN_00055710 @ 0x00055710
 * address symbols (name @ address):
 *   g_bt_le_legacy_adv                       @ 0x20002018
 */
/* Reconstructed FUN_00055710 @ 0x55710, exact extent 6 bytes. */
#include <stdint.h>

typedef uint32_t (*dispatch_fn_t)(uintptr_t object);

uint32_t bt_le_adv_legacy_invoke(dispatch_fn_t dispatch)
{
    return dispatch(((unsigned long)g_bt_le_legacy_adv) /*=0x20002018*/);
}
