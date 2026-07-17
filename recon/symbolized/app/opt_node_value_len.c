#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007c408 @ 0x0007c408
 * public-name: opt_node_value_len
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   opt_node_value_len                       <= FUN_0007c408 @ 0x0007c408
 */
/* Reconstructed FUN_0007c408 @ 0x7c408  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
typedef unsigned int (*fnptr_t)(void);

unsigned int opt_node_value_len(int param_1)
{
    if (param_1 == 0) return 0;
    int *p14 = *(int **)(param_1 + 0x14);
    if (p14 != 0) {
        fnptr_t fn = *(fnptr_t *)((char *)p14 + 4);
        if (fn != 0) {
            return fn();
        }
    }
    return *(unsigned int *)(param_1 + 0x10);
}
