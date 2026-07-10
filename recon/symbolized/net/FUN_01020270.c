#include "g1_net_symbols.h"
/* net-core FUN_01020270 @ 0x1020270  (parity 300 trials PROVEN) */

extern void FUN_01008d00(unsigned int, unsigned int, unsigned int, unsigned int) __attribute__((noreturn));
void FUN_01020270(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4){
  if (param_1 < 0x97) {
    *(volatile short *)(((uintptr_t)&g_nrf802154_core_state) /*=0x210015f0*/ + 0x1c) = (short)param_1;
    return;
  }
  FUN_01008d00(0x3e, 0x1f5, param_3, param_4);
  __builtin_unreachable();
}

