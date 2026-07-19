#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000858da @ 0x000858da
 * public-name: rpmsg_release_rx_buffer
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   rpmsg_release_rx_buffer                  <= FUN_000858da @ 0x000858da
 */
/* Reconstructed FUN_000858da @ 0x858da  (parity: 300/300 trials, PROVEN) */

typedef void (*fnptr)(void);

void rpmsg_release_rx_buffer(int param_1, int param_2)
{
    if (param_1 != 0 && *(int *)(param_1 + 0x20) != 0 && param_2 != 0) {
        int p2 = *(int *)(param_1 + 0x20);
        fnptr f = *(fnptr *)(p2 + 0x80);
        if (f != 0) {
            f();
        }
    }
}
