#include "g1_app_symbols.h"
/* named: md5_init */
/* Reconstructed md5_init @ 0x49aa0  (parity: 300/300 trials, PROVEN) */

void md5_init(unsigned int *param_1)
{
  unsigned int iVar1;
  param_1[0] = 0;
  param_1[1] = 0;
  iVar1 = 0x67452301;
  param_1[2] = iVar1;
  param_1[3] = iVar1 + 0x88888888;
  param_1[4] = iVar1 + 0x3175b9fd;
  param_1[5] = iVar1 + 0xa8ed3175;
}

