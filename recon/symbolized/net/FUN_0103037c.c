#include "g1_net_symbols.h"
/* net-core FUN_0103037c @ 0x103037c  (parity 300 trials PROVEN) */

int FUN_0103037c(unsigned int param_1)
{
  unsigned int DAT_01030388 = ((uintptr_t)&g_net_entry32_tbl) /*=0x21004814*/;
  unsigned char b = (unsigned char)param_1;
  return DAT_01030388 + (unsigned int)b * 0x20;
}

