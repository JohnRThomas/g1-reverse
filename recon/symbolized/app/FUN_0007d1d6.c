#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007d1d6 @ 0x0007d1d6
 * public-name: FUN_0007d1d6
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   rate_limited_elapsed_seconds_tick        <= FUN_0004a46c @ 0x0004a46c
 */
/* Reconstructed FUN_0007d1d6 @ 0x7d1d6  (parity: 300/300 trials, PROVEN) */

extern void rate_limited_elapsed_seconds_tick(unsigned int, unsigned int);
extern void FUN_00016574(unsigned int);

void FUN_0007d1d6(int param_1, unsigned int param_2)
{
  int iVar1;
  char *base = (char*)param_1;
  int *p1 = *(int **)(base + 0xff4);

  iVar1 = *(int*)((char*)p1 + 0x164);
  if (iVar1 != 0) {
    **(int **)(base + 0xfec) = iVar1;
  }
  rate_limited_elapsed_seconds_tick(param_2, 0);
  p1 = *(int **)(base + 0xff4);
  if (*(int*)((char*)p1 + 0x164) != 0) {
    *(unsigned int*)((char*)p1 + 0x164) = **(unsigned int **)(base + 0xfec);
  }
  FUN_00016574(**(unsigned int **)(base + 0xfec));
  return;
}
