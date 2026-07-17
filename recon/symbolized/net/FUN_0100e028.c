#include "g1_net_symbols.h"
/* net-core FUN_0100e028 @ 0x100e028  (parity 300 trials PROVEN) */

void FUN_0100e028(char *param_1, unsigned int *param_2)
{
  *(unsigned int *)(param_1 + 9) = param_2[0];
  *(unsigned short *)(param_1 + 0xd) = *(unsigned short *)((char*)param_2 + 4);
}
