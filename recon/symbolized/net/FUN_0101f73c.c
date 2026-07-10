#include "g1_net_symbols.h"
/* net-core FUN_0101f73c @ 0x101f73c  (parity 300 trials PROVEN) */

extern void FUN_010294d2(unsigned int a, unsigned int b);

void FUN_0101f73c(void)
{
  FUN_010294d2(((uintptr_t)&g_net_sdc_resource_cfg) /*=0x21001230*/ + 0x20c, ((uintptr_t)&g_net_cfg_copy_dst_a) /*=0x210004e0*/);
  FUN_010294d2(((uintptr_t)&g_net_sdc_resource_cfg) /*=0x21001230*/ + 0x210, ((uintptr_t)&g_net_cfg_copy_dst_b) /*=0x210004e8*/);
}

