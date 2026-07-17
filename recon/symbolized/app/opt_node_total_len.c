#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007c41c @ 0x0007c41c
 * public-name: opt_node_total_len
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   opt_node_header_len                      <= FUN_0007c3ea @ 0x0007c3ea
 *   opt_node_value_len                       <= FUN_0007c408 @ 0x0007c408
 *   opt_node_total_len                       <= FUN_0007c41c @ 0x0007c41c
 */
/* Reconstructed FUN_0007c41c @ 0x7c41c  (parity: 300/300 trials, PROVEN) */

extern int opt_node_header_len(void);
extern int opt_node_value_len(unsigned int param_1);

int opt_node_total_len(unsigned int param_1)
{
    int iVar1 = opt_node_header_len();
    int iVar2 = opt_node_value_len(param_1);
    return iVar2 + iVar1;
}
