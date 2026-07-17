#include "g1_net_symbols.h"
/* net-core FUN_01033af8 @ 0x1033af8  (parity 300 trials PROVEN) */

volatile unsigned char *DAT_01033b10 = (volatile unsigned char *)((unsigned long)&g_net_radio_busy_flag) /*=0x21006458*/;
unsigned int FUN_01033af8(unsigned char param_1) {
  unsigned char bVar1 = *DAT_01033b10;
  if (bVar1 == 0) {
    *(volatile unsigned char *)(((unsigned long)&g_esb_state) /*=0x21004a94*/ + 0xa) = param_1;
    return (unsigned int)bVar1;
  }
  return 0xfffffff0;
}
