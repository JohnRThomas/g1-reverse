#include "g1_net_symbols.h"
/* net-core FUN_0101f764 @ 0x101f764  (parity 300 trials PROVEN) */

extern void FUN_010294d2(unsigned int, unsigned int);

void FUN_0101f764(void)
{
  unsigned int base = ((uintptr_t)&g_net_sdc_resource_cfg) /*=0x21001230*/;

  FUN_010294d2(base + 0x20c, ((uintptr_t)&g_net_radio_cbset4_ptr0) /*=0x21000518*/);
  FUN_010294d2(base + 0x210, ((uintptr_t)&g_net_radio_cbset4_ptr1) /*=0x21000520*/);
  FUN_010294d2(base + 0x214, ((uintptr_t)&g_net_radio_cbset4_ptr2) /*=0x21000510*/);
}

