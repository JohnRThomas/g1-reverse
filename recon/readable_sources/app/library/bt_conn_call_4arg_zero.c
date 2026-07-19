#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000813ca @ 0x000813ca
 * public-name: bt_conn_call_4arg_zero
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_log_msg_runtime_create                 <= FUN_0004d944 @ 0x0004d944
 *   bt_conn_call_4arg_zero                   <= FUN_000813ca @ 0x000813ca
 */
/* Reconstructed FUN_000813ca @ 0x813ca  (parity: 300/300 trials, PROVEN) */

extern void z_log_msg_runtime_create(unsigned, unsigned, unsigned, unsigned);
void bt_conn_call_4arg_zero(unsigned r0, unsigned r1, unsigned r2)
{
    z_log_msg_runtime_create(r0, r1, r2, 0);
}
