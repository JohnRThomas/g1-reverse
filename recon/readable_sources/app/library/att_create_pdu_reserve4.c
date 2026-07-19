#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0008181a @ 0x0008181a
 * public-name: att_create_pdu_reserve4
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_conn_create_pdu_timeout               <= FUN_000569ec @ 0x000569ec
 *   att_create_pdu_reserve4                  <= FUN_0008181a @ 0x0008181a
 */
/* Reconstructed FUN_0008181a @ 0x8181a  (parity: 300/300 trials, PROVEN) */

extern void bt_conn_create_pdu_timeout(unsigned int, int);
void att_create_pdu_reserve4(unsigned int param_1, int param_2)
{
    bt_conn_create_pdu_timeout(param_1, param_2 + 4);
}
