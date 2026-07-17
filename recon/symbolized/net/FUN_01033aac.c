#include "g1_net_symbols.h"
/* net-core FUN_01033aac @ 0x1033aac  (parity 300 trials PROVEN) */

volatile unsigned char *DAT_01033ac4 = (volatile unsigned char *)((unsigned long)&g_net_radio_busy_flag) /*=0x21006458*/;
unsigned int FUN_01033aac(unsigned char param_1) {
  unsigned char bVar1 = *DAT_01033ac4;
  if (bVar1 == 0) {
    *(volatile unsigned char *)(((unsigned long)&g_net_radio_crc_scratch) /*=0x21000684*/ + 0x12) = param_1;
    return (unsigned int)bVar1;
  }
  return 0xfffffff0;
}
