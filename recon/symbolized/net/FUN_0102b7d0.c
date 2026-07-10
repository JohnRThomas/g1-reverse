#include "g1_net_symbols.h"
/* net-core FUN_0102b7d0 @ 0x102b7d0  (parity 300 trials PROVEN) */

typedef void (*fptr_t)(int);
void FUN_0102b7d0(int param_1)
{
  volatile unsigned char *A = (volatile unsigned char*)((uintptr_t)&g_net_evt_notify_disabled_flag) /*=0x21004fa5*/;
  volatile unsigned char *B = (volatile unsigned char*)((uintptr_t)&g_net_evt_last_notified_state) /*=0x21004fa6*/;
  fptr_t *Cp = (fptr_t*)((uintptr_t)&g_net_evt_callback_fn) /*=0x2100463c*/;
  if (*A == 0) {
    if (param_1 == 0) {
      if (*B != 0) {
        (*Cp)(1);
        *B = 0;
      }
    } else if (*B == 0) {
      (*Cp)(0);
      *B = 1;
    }
  }
}

