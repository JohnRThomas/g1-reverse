#include "g1_net_symbols.h"
/* net-core FUN_01036e90 @ 0x1036e90  (parity 300 trials PROVEN) */

unsigned int FUN_01036e90(int param_1)
{
  unsigned int uVar1;

  if (*(volatile unsigned short *)(param_1 + 0xe) < 0x80) {
    uVar1 = *(volatile unsigned int *)((uintptr_t)&g_net_ctx_active_count) /*=0x21004b64*/;
    if (uVar1 == 0) goto done;
    if ((*(volatile int *)((uintptr_t)&g_net_pipe_index_limit) /*=0x21004b60*/ <= (int)*(volatile signed char *)(param_1 + 0xe)) &&
        ((*(volatile unsigned char *)(param_1 + 0xd) & 0x1f) == 0)) {
      uVar1 = (unsigned int)param_1 - ((uintptr_t)&g_net_dlist_sentinel) /*=0x210043a8*/;
      if (uVar1 != 0) {
        uVar1 = 1;
      }
      goto done;
    }
  }
  uVar1 = 0;
done:
  return uVar1 & 1;
}

