#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00085c26 @ 0x00085c26
 * public-name: FUN_00085c26
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed FUN_00085c26 @ 0x85c26  (parity: 300/300 trials, PROVEN) */

extern unsigned long long FUN_00085c12(int a);

void FUN_00085c26(int param_1)
{
    int iVar1 = *(int *)(param_1 + 0x14);
    unsigned long long uVar2 = FUN_00085c12(iVar1);
    if ((int)uVar2 != 0 && iVar1 != 0) {
        *(int *)(iVar1 + 0xc) = (int)(uVar2 >> 32);
    }
}
