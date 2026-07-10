#include "g1_app_symbols.h"
/* named: fb_blit_rows_halved */
/* Reconstructed fb_blit_rows_halved @ 0x7d5f2  (parity: 154/300 trials, PROVEN) */

extern void memcpy(int a, int b, int c);
void fb_blit_rows_halved(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6,int param_7)
{
  int *piVar1;
  int *piVar2;
  int iVar3;

  piVar1 = (int *)(param_1 + param_5 * 4);
  piVar2 = (int *)(param_1 + param_3 * 4);
  for (iVar3 = 0; iVar3 < param_6; iVar3 = iVar3 + 1) {
    memcpy(*piVar2 + param_2 / 2,*piVar1 + param_4 / 2,param_7 / 2);
    piVar1 = piVar1 + 1;
    piVar2 = piVar2 + 1;
  }
}

