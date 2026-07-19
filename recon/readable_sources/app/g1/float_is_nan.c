#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0000e938 @ 0x0000e938
 * public-name: float_is_nan
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   __extendsfdf2                            <= FUN_0000d848 @ 0x0000d848
 *   double_is_unordered                      <= FUN_0000de2c @ 0x0000de2c
 *   float_is_nan                             <= FUN_0000e938 @ 0x0000e938
 */
/* Reconstructed FUN_0000e938 @ 0xe938  (parity: 300/300 trials, PROVEN) */

extern unsigned long long __extendsfdf2(int a);
extern int double_is_unordered(int a,int b,int c,int d,int e);
int float_is_nan(float param_1) {
    int r0;
    __builtin_memcpy(&r0, &param_1, 4);
    unsigned long long uVar3 = __extendsfdf2(r0);
    int lo = (int)uVar3;
    int hi = (int)(uVar3 >> 32);
    int iVar1 = double_is_unordered(lo, hi, lo, hi, 0);
    if (iVar1 != 0) iVar1 = 1;
    return iVar1;
}
