#include "g1_net_symbols.h"
/* net-core FUN_010353b4 @ 0x10353b4  (parity 300 trials PROVEN) */

typedef void (*fp3_t)(unsigned int, unsigned int, unsigned int);
extern void FUN_0103b522(int param_1);

void FUN_010353b4(int param_1)
{
  if (param_1 != 0) {
    if ((*(volatile short *)(param_1 + 0x24) != *(volatile short *)(param_1 + 0xa)) &&
        (3 < *(volatile unsigned char *)((uintptr_t)&g_net_debug_trace_level) /*=0x21004b04*/) &&
        (*(volatile fp3_t *)((uintptr_t)&g_net_debug_trace_cb) /*=0x21004b08*/ != (fp3_t)0)) {
      (*(volatile fp3_t *)((uintptr_t)&g_net_debug_trace_cb) /*=0x21004b08*/)(4, ((uintptr_t)&rodata_103e867) /*=0x103e867*/, *(volatile unsigned int *)(param_1 + 4));
    }
    FUN_0103b522(param_1);
    return;
  }
  return;
}

