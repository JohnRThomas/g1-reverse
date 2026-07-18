#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00080a46 @ 0x00080a46
 * public-name: img_mgmt_active_slot
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   img_mgmt_active_slot                     <= FUN_00080a46 @ 0x00080a46
 */
/* Reconstructed FUN_00080a46 @ 0x80a46  (parity: 300/300 trials, PROVEN) */

int img_mgmt_active_slot(int param_1)
{
    return param_1 << 1;
}
