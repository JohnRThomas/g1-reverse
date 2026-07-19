#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000858ec @ 0x000858ec
 * public-name: rpmsg_get_tx_payload_buffer
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   rpmsg_get_tx_payload_buffer              <= FUN_000858ec @ 0x000858ec
 */
/* Reconstructed FUN_000858ec @ 0x858ec  (parity: 300/300 trials, PROVEN) */

typedef unsigned int (*fnptr_t)(void);

unsigned int rpmsg_get_tx_payload_buffer(int param_1, int param_2)
{
    if (param_1 != 0) {
        int *p20 = *(int **)(param_1 + 0x20);
        if (p20 != 0 && param_2 != 0) {
            fnptr_t fn = *(fnptr_t *)((char *)p20 + 0x84);
            if (fn != 0) {
                return fn();
            }
        }
    }
    return 0;
}
