#include "g1_net_symbols.h"
/* net-core FUN_0100d738 @ 0x100d738  (parity 300 trials PROVEN) */

#include <stdint.h>
int FUN_0100d738(int param_1)
{
  volatile unsigned char *p = (volatile unsigned char *)((uintptr_t)&g_net_rssi_cal_offset) /*=0x21000ea6*/;
  int b = *p;
  int8_t neg = (int8_t)(0 - b);
  int r0 = param_1 + neg;
  if (r0 > 0x14) {
    return 0x14;
  }
  if (r0 < -0x7f) {
    return -0x7f;
  }
  return (int8_t)r0;
}

