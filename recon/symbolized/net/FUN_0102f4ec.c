#include "g1_net_symbols.h"
/* net-core FUN_0102f4ec @ 0x102f4ec CFG_VERIFY_PREFIX_FIRST */
#include <stdint.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"

void FUN_0102f4ec(void)
{
  volatile unsigned int *p = (volatile unsigned int *)0xe000ed00;
  __DSB();
  p[3] = 0x05fa0004 | (p[3] & 0x700);
  __DSB();
  while (1) { }
}
