#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007de70 @ 0x0007de70
 * public-name: FUN_0007de70
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed FUN_0007de70 @ 0x7de70  (parity: 300/300 trials, PROVEN) */

unsigned int FUN_0007de70(unsigned int param_1, int param_2)
{
    unsigned int iVar1;
    if (param_1 < 0x8000) {
        iVar1 = 4;
    } else {
        iVar1 = 8;
    }
    return (unsigned int)(param_2 + 7 + iVar1) >> 3;
}
