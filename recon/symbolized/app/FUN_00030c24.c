#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00030c24 @ 0x00030c24
 * public-name: FUN_00030c24
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_misc_dev_handle_2418                   @ 0x20002418
 */
/* Reconstructed FUN_00030c24 @ 0x30c24  (parity: 300/300 trials, PROVEN) */

typedef int (*fnptr)(unsigned int, void *, int, int);

int FUN_00030c24(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  int iVar1;
  unsigned int local_20;
  unsigned int uStack_1c;
  unsigned char local_18;
  unsigned int local_14;
  unsigned int uStack_10;
  unsigned char local_c;
  unsigned int base;
  int field;
  fnptr fp;
  local_18 = 0;
  local_c = 7;
  local_20 = param_1;
  uStack_1c = param_2;
  local_14 = param_3;
  uStack_10 = param_4;
  base = *(volatile unsigned int *)((unsigned long)&g_misc_dev_handle_2418) /*=0x20002418*/;
  field = *(int *)(base + 8);
  fp = *(fnptr *)(field + 8);
  iVar1 = fp(base, &local_20, 2, 0x12);
  if (iVar1 != 0) iVar1 = 1;
  return -iVar1;
}
