#include "g1_net_symbols.h"
/* net-core FUN_0100a4d0 @ 0x100a4d0  (parity 300 trials PROVEN) */

extern unsigned int FUN_01027af2(unsigned short);
extern unsigned int FUN_01027b32(unsigned short);
unsigned short FUN_0100a4d0(void)
{
  volatile unsigned short *g = (volatile unsigned short*)((unsigned long)&g_net_storage_area_id) /*=0x21000bc0*/;
  unsigned short uVar1 = (unsigned short)FUN_01027af2(*g);
  unsigned short uVar2 = (unsigned short)FUN_01027b32(*g);
  if (uVar2 < uVar1) uVar2 = uVar1;
  return uVar2;
}
