#include "g1_net_symbols.h"
/* net-core FUN_01018bf8 @ 0x1018bf8  (parity 300 trials PROVEN) */

extern unsigned char FUN_0100d760(void);
extern unsigned int  FUN_010187e0(unsigned char *, unsigned int);
extern void          FUN_010196e0(void);

unsigned int FUN_01018bf8(unsigned char *param_1)
{
  unsigned char uVar2;
  unsigned char bVar1;
  volatile unsigned char *out = (volatile unsigned char*)((uintptr_t)&g_net_ble_pending_channel_idx) /*=0x2100001c*/;

  uVar2 = FUN_0100d760();
  bVar1 = *param_1;
  *out = uVar2;
  if ((bVar1 & 0xf) == 7) {
    return FUN_010187e0(param_1, 3);
  }
  FUN_010196e0();
  return 1;
}

