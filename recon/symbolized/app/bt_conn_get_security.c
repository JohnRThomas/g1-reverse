#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000814e2 @ 0x000814e2
 * public-name: bt_conn_get_security
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_conn_get_security                     <= FUN_000814e2 @ 0x000814e2
 */
/* Reconstructed FUN_000814e2 @ 0x814e2  (parity: 300/300 trials, PROVEN) */

unsigned char bt_conn_get_security(char *param_1)
{
    return *(unsigned char *)(param_1 + 9);
}
