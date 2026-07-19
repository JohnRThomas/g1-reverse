#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007f406 @ 0x0007f406
 * public-name: gatt_dm_log_helper
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_log_msg_runtime_create                 <= FUN_0004d944 @ 0x0004d944
 *   gatt_dm_log_helper                       <= FUN_0007f406 @ 0x0007f406
 */
/* Reconstructed FUN_0007f406 @ 0x7f406  (parity: 300/300 trials, PROVEN) */

extern void z_log_msg_runtime_create(unsigned, unsigned, unsigned, unsigned);
void gatt_dm_log_helper(unsigned r0, unsigned r1, unsigned r2)
{
    z_log_msg_runtime_create(r0, r1, r2, 0);
}
