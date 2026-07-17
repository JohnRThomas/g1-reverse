#include "g1_net_symbols.h"
/* net-core FUN_0102df04 @ 0x102df04  (parity 300 trials PROVEN) */
/* FUN_0102df04: entry is a 2-instr tail-thunk (ldr r0,[pc,#4]; b.w 0x102ce14)
   -- immediate tail branch out of the function's own body. The harness's
   out-of-body hook treats this as a single oracle call whose result is
   returned directly (LR unchanged from entry). Model as one tail call. */
extern unsigned int FUN_0102ce14(unsigned int a);
unsigned int FUN_0102df04(void)
{
  return FUN_0102ce14(((unsigned long)&g_net_periodic_work_obj) /*=0x2100086c*/);
}
