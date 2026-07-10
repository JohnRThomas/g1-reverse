#include "g1_app_symbols.h"
/* named: strcpy */
/* Reconstructed strcpy @ 0x86fee  (parity: 300/300 trials, PROVEN) */

void strcpy(char *param_1,char *param_2)
{
  char cVar1;
  do {
    cVar1 = *param_2;
    *param_1 = cVar1;
    param_2 = param_2 + 1;
    param_1 = param_1 + 1;
  } while (cVar1 != 0);
}

