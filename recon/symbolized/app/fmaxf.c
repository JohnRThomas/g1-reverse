#include "g1_app_symbols.h"
/* named: fmaxf */
/* Reconstructed fmaxf @ 0x86902  (parity: 300/300 trials, PROVEN) */

extern int __fpclassifyf(float x);
float fmaxf(float param_1,float param_2)
{
  int iVar1;
  iVar1 = __fpclassifyf(param_1);
  if ((iVar1 == 0) ||
     ((iVar1 = __fpclassifyf(param_2), iVar1 != 0) &&
      (param_1 == param_2 || (param_1 < param_2) != ((param_1 != param_1) || (param_2 != param_2))))) {
    param_1 = param_2;
  }
  return param_1;
}

