#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007c956 @ 0x0007c956
 * public-name: st25dv_ipc_request
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ipc_ept_op_b_locked_retry                <= FUN_000257ec @ 0x000257ec
 *   st25dv_ipc_request                       <= FUN_0007c956 @ 0x0007c956
 */
/* Reconstructed FUN_0007c956 @ 0x7c956  (parity: 300/300 trials, PROVEN) */

extern int ipc_ept_op_b_locked_retry(int, unsigned int, unsigned int, int);

unsigned int st25dv_ipc_request(unsigned int param_1, int param_2)
{
    if (param_2 != 0) {
        return ipc_ept_op_b_locked_retry(param_1, 0x17, param_2, 1);
    }
    return 0xffffffea;
}
