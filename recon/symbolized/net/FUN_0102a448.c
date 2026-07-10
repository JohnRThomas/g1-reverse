#include "g1_net_symbols.h"
/* net-core FUN_0102a448 @ 0x102a448  (parity 300 trials PROVEN) */

extern void FUN_0103b53a(unsigned int, unsigned int, unsigned int, unsigned int);
unsigned int FUN_0102a448(unsigned int param_1, unsigned int param_2) {
  FUN_0103b53a(((uintptr_t)&g_net_ctrl_rx_buf) /*=0x21004b9f*/, param_1, param_2, 0xfc);
  *(volatile unsigned int *)((uintptr_t)&g_net_ctrl_report_len) /*=0x210045e4*/ = param_2;
  return 0;
}

