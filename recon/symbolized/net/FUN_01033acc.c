#include "g1_net_symbols.h"
/* net-core FUN_01033acc @ 0x1033acc  (parity 300 trials PROVEN) */

unsigned int FUN_01033acc(unsigned int param_1)
{
  volatile unsigned char *p1 = (volatile unsigned char *)((uintptr_t)&g_net_radio_busy_flag) /*=0x21006458*/;
  unsigned char b = *p1;
  if (b != 0) {
    return 0xfffffff0;
  }
  if (param_1 < 0x65) {
    volatile unsigned char *p2 = (volatile unsigned char *)((uintptr_t)&g_net_radio_crc_scratch) /*=0x21000684*/;
    p2[0x13] = (unsigned char)param_1;
    return (unsigned int)b;
  }
  return 0xffffffea;
}

