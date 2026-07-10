#include "g1_app_symbols.h"
/* named: FUN_00080fba */
/* Reconstructed FUN_00080fba @ 0x80fba  (parity: 300/300 trials, PROVEN) */

void FUN_00080fba(unsigned int *param_1, unsigned int *param_2)
{
  *param_1 = *param_2;
  *(unsigned short *)((unsigned char*)param_1 + 4) = *(unsigned short *)((unsigned char*)param_2 + 4);
}

