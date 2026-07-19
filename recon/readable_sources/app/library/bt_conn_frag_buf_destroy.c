#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000571dc @ 0x000571dc
 * public-name: bt_conn_frag_buf_destroy
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_conn_create_pdu_timeout               <= FUN_000569ec @ 0x000569ec
 *   bt_conn_frag_buf_destroy                 <= FUN_000571dc @ 0x000571dc
 * address symbols (name @ address):
 *   g_bt_conn_frag_pool                      @ 0x20003b18
 */
/* Reconstructed FUN_000571dc @ 0x571dc  (parity: 300/300 trials, PROVEN) */

extern void bt_conn_create_pdu_timeout(unsigned int, unsigned int);
void bt_conn_frag_buf_destroy(unsigned int param_1)
{
  bt_conn_create_pdu_timeout(((unsigned long)&g_bt_conn_frag_pool) /*=0x20003b18*/, param_1);
}
