#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00085d5c @ 0x00085d5c
 * public-name: FUN_00085d5c
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed FUN_00085d5c @ 0x85d5c  (parity: 300/300 trials, PROVEN) */

int FUN_00085d5c(int param_1)
{
    if (param_1 != 0 && *(char *)(param_1 + 0x10) != 0) {
        return *(int *)(param_1 + 0xc) == 0;
    }
    return 1;
}
