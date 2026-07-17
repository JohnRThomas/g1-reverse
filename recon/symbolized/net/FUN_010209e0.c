#include "g1_net_symbols.h"
/* net-core FUN_010209e0 @ 0x10209e0  (parity 300 trials PROVEN) */

volatile unsigned int *const DAT_010209ec = (volatile unsigned int *)((unsigned long)&rodata_103c4d0) /*=0x103c4d0*/;
unsigned int FUN_010209e0(int param_1)
{
  return *(volatile unsigned int *)((char *)DAT_010209ec + param_1 * 4 + 0x28);
}
