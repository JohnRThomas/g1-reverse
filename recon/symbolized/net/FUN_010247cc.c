#include "g1_net_symbols.h"
/* net-core FUN_010247cc @ 0x10247cc  (parity 300 trials PROVEN) */

static volatile unsigned char * const DAT_010247d8 = (volatile unsigned char *)((uintptr_t)&g_154_critical_section_nest_cnt) /*=0x21001bd0*/;
signed char FUN_010247cc(void)
{
  unsigned int v = DAT_010247d8[0xd];
  if (v != 0) v = 1;
  return (signed char)v;
}

