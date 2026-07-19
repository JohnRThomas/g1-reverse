#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007de70 @ 0x0007de70
 * public-name: log_msg_compute_wlen
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   log_msg_compute_wlen                     <= FUN_0007de70 @ 0x0007de70
 */
/* Reconstructed FUN_0007de70 @ 0x7de70  (parity: 300/300 trials, PROVEN) */

unsigned int log_msg_compute_wlen(unsigned int param_1, int param_2)
{
    unsigned int iVar1;
    if (param_1 < 0x8000) {
        iVar1 = 4;
    } else {
        iVar1 = 8;
    }
    return (unsigned int)(param_2 + 7 + iVar1) >> 3;
}
