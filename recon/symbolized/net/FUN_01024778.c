#include "g1_net_symbols.h"
/* net-core FUN_01024778 @ 0x1024778  (parity 300 trials PROVEN) */
#include <stdint.h>
/* net-core FUN_01024778 @ 0x1024778  (parity 300 trials PROVEN) */

extern void FUN_01024aa8(void);
extern void FUN_010256dc(int,int) __attribute__((noreturn));
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"

volatile unsigned char *const G6 = (volatile unsigned char*)((unsigned long)&g_net_irq_lock_nest_cnt) /*=0x21001bd6*/;
volatile unsigned char *const Gf = (volatile unsigned char*)((unsigned long)&g_net_irq_lock_suppress_flag) /*=0x21001bdf*/;

void FUN_01024778(void)
{
  unsigned int primask;
  primask = __get_PRIMASK();
  __disable_irq();
  if (*G6 == 0) {
    FUN_010256dc(0x6d,300);
  }
  *G6 = *G6 - 1;
  if ((*G6 == 0) && (*Gf == 0)) {
    FUN_01024aa8();
  }
  if (primask == 0) {
    __enable_irq();
  }
}
