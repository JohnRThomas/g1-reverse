#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007e35c @ 0x0007e35c
 * public-name: idx_inc
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   idx_inc                                  <= FUN_0007e35c @ 0x0007e35c
 */
/* Reconstructed FUN_0007e35c @ 0x7e35c  (parity: 300/300 trials, PROVEN) */

unsigned int idx_inc(int param_1,int param_2,int param_3)
{
  unsigned int uVar1 = (unsigned int)(param_3 + param_2);
  unsigned int uVar2 = *(volatile unsigned int *)(param_1 + 0x24);
  if ((*(volatile int *)(param_1 + 0x10) << 0x1f) < 0) {
    uVar1 = uVar1 & (uVar2 - 1);
  } else if (uVar2 <= uVar1) {
    uVar1 = uVar1 - uVar2;
  }
  return uVar1;
}
