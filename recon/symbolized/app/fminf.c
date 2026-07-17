#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0008693c @ 0x0008693c
 * public-name: fminf
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   __fpclassifyf                            <= FUN_00075980 @ 0x00075980
 *   fminf                                    <= FUN_0008693c @ 0x0008693c
 */
/* Reconstructed FUN_0008693c @ 0x8693c  (parity: 300/300 trials, PROVEN) */

extern int __fpclassifyf(float x);
float fminf(float param_1,float param_2)
{
  int iVar1;
  iVar1 = __fpclassifyf(param_1);
  if ((iVar1 == 0) || ((iVar1 = __fpclassifyf(param_2), iVar1 != 0) && !(param_1 < param_2))) {
    param_1 = param_2;
  }
  return param_1;
}
