/* readable reconstruction; identity: FUN_00055710 @ 0x00055710
 * public-name: FUN_00055710
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_bt_le_legacy_adv                       @ 0x20002018
 */
/* Reconstructed FUN_00055710 @ 0x55710, exact extent 6 bytes. */
#include <stdint.h>

typedef uint32_t (*dispatch_fn_t)(uintptr_t object);

uint32_t FUN_00055710(dispatch_fn_t dispatch)
{
    return dispatch(0x20002018u);
}
