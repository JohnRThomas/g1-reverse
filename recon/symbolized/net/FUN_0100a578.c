#include "g1_net_symbols.h"
/* net-core FUN_0100a578 @ 0x100a578  (parity 300 trials PROVEN) */

extern void FUN_0100a50c(unsigned int, unsigned char, unsigned char);
void FUN_0100a578(void) {
  volatile unsigned int *DAT_0100a594 = (volatile unsigned int *)((unsigned long)&g_net_retry_handle) /*=0x21000bc4*/;
  volatile unsigned char *DAT_0100a598 = (volatile unsigned char *)((unsigned long)&g_net_retry_param2) /*=0x21000bc8*/;
  volatile unsigned char *DAT_0100a59c = (volatile unsigned char *)((unsigned long)&g_sdc_last_cfg_param3) /*=0x21000bc9*/;
  FUN_0100a50c(*DAT_0100a594, *DAT_0100a598, *DAT_0100a59c);
}
