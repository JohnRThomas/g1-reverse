#include "g1_net_symbols.h"
/* net-core FUN_010091cc @ 0x10091cc  (parity 300 trials PROVEN) */

extern void FUN_0101e94c(void);
volatile unsigned char *DAT_010091e4 = (volatile unsigned char *)((uintptr_t)&g_net_layout_count_table) /*=0x21000a30*/;
unsigned int FUN_010091cc(void) {
  unsigned int uVar1;
  if (*(volatile char *)(DAT_010091e4 + 0x2c) == 0) {
    FUN_0101e94c();
    uVar1 = 0;
  } else {
    uVar1 = 0xffffffff;
  }
  return uVar1;
}

