#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000810f2 @ 0x000810f2
 * public-name: bt_id_set_random_addr_checked
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_id_set_random_addr_checked            <= FUN_000810f2 @ 0x000810f2
 */
/* Reconstructed FUN_000810f2 @ 0x810f2  (parity: 300/300 trials, PROVEN) */
extern int set_random_address(int a, int b, int c, int d);
int bt_id_set_random_addr_checked(int param_1, int param_2, int param_3, int param_4){
    if (param_1 == 0 || param_2 == 0) return -0x16;
    return set_random_address(param_2, param_2, param_3, param_4);
}
