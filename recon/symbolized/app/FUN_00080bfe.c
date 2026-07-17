#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00080bfe @ 0x00080bfe
 * public-name: FUN_00080bfe
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed FUN_00080bfe @ 0x80bfe  (parity: 300/300 trials, PROVEN) */

int FUN_00080bfe(int *param_1)
{
    int iVar1 = *(int*)((char*)param_1 + 0x40);
    if (iVar1 != 0) {
        iVar1 = iVar1 + 0x18;
    }
    return iVar1;
}
