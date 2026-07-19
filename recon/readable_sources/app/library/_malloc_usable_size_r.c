#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00087996 @ 0x00087996
 * public-name: _malloc_usable_size_r
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   _malloc_usable_size_r                    <= FUN_00087996 @ 0x00087996
 */
/* Reconstructed FUN_00087996 @ 0x87996  (parity: 300/300 trials, PROVEN) */

int _malloc_usable_size_r(unsigned int param_1,char *param_2)
{
  int iVar1 = *(int *)(param_2 - 4);
  int r0 = iVar1 - 4;
  if (iVar1 < 0) {
    r0 = r0 + *(int *)(param_2 + r0);
  }
  return r0;
}
