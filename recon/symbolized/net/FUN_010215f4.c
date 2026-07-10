#include "g1_net_symbols.h"
/* net-core FUN_010215f4 @ 0x10215f4  (parity 300 trials PROVEN) */

int FUN_010215f4(int param_1, int param_2) {
  volatile unsigned short *DAT_0102160c = (volatile unsigned short *)"%02X-0x%02X\n" /*=0x103c5c4*/;
  unsigned int DAT_01021610 = 0x10624dd3;
  return param_1 - 2 + (unsigned int)(((unsigned long long)DAT_01021610 * (unsigned long long)(DAT_0102160c[param_2] + 999)) >> 0x26);
}

