#include "g1_net_symbols.h"
/* net-core FUN_010339e4 @ 0x10339e4  (parity 300 trials PROVEN) */

extern unsigned long long FUN_0103a80c(unsigned int *p);

unsigned int FUN_010339e4(unsigned int *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  unsigned int r1v = *(volatile unsigned char *)((unsigned long)&g_net_radio_busy_flag) /*=0x21006458*/;
  if (r1v == 0) {
    if (param_1 == 0) {
      return 0xffffffea;
    } else {
      unsigned int uVar3 = *param_1;
      *(volatile unsigned int *)((unsigned long)&g_net_radio_crc_scratch) /*=0x21000684*/ = uVar3;
      unsigned long long rv = FUN_0103a80c((unsigned int *)((unsigned long)&g_net_radio_crc_scratch) /*=0x21000684*/);
      unsigned int rev = __builtin_bswap32((unsigned int)rv);
      *(volatile unsigned int *)(REG_41008000 /*=0x41008000*/ + 0x51c) = rev;
      return (unsigned int)(rv >> 32);
    }
  } else {
    return 0xfffffff0;
  }
}
