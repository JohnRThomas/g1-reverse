#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007c932 @ 0x0007c932
 * public-name: st25dv_ipc_request_chip_ids
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ipc_ept_op_b_locked_retry                <= FUN_000257ec @ 0x000257ec
 *   st25dv_ipc_request_chip_ids              <= FUN_0007c932 @ 0x0007c932
 */
/* Reconstructed FUN_0007c932 @ 0x7c932  (parity: 300/300 trials, PROVEN) */

extern unsigned int ipc_ept_op_b_locked_retry(unsigned int a, unsigned int b, unsigned int c, unsigned int d);

unsigned int st25dv_ipc_request_chip_ids(unsigned int param_1, int param_2)
{
    if (param_2 != 0) {
        return ipc_ept_op_b_locked_retry(param_1, 0x18, param_2, 8);
    }
    return 0xffffffea;
}
