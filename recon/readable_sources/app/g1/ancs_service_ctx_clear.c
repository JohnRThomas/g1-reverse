#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007f69e @ 0x0007f69e
 * public-name: ancs_service_ctx_clear
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ancs_service_ctx_clear                   <= FUN_0007f69e @ 0x0007f69e
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 */
/* Reconstructed FUN_0007f69e @ 0x7f69e  (parity: 300/300 trials, PROVEN) */

extern int memset_bytes(int a,int b,int c,int d,int e);
int ancs_service_ctx_clear(int param_1, int param_2, int param_3, int param_4) {
    if (param_1 == 0) {
        return -22;
    }
    memset_bytes(param_1, 0, 0xa2c, param_4, param_4);
    return 0;
}
