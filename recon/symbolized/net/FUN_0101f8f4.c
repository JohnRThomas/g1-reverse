#include "g1_net_symbols.h"
/* net-core FUN_0101f8f4 @ 0x101f8f4  (parity 300 trials PROVEN) */

extern unsigned int FUN_010246cc(void);

void FUN_0101f8f4(void)
{
  unsigned int uVar1;
  unsigned char uVar2;
  int iVar3;
  volatile unsigned short *tbl16 = (volatile unsigned short*)((uintptr_t)&rodata_103c3b0) /*=0x103c3b0*/;
  volatile unsigned char  *tbl8  = (volatile unsigned char*) ((uintptr_t)&rodata_103c3b0) /*=0x103c3b0*/;
  volatile unsigned char  *out   = (volatile unsigned char*) ((uintptr_t)&g_net_radio_tx_power_level) /*=0x2100144a*/;

  uVar1 = FUN_010246cc();
  iVar3 = 0;
  do {
    if (uVar1 <= tbl16[iVar3 * 2]) {
      uVar2 = tbl8[iVar3 * 4 + 2];
      goto LAB;
    }
    iVar3 = iVar3 + 1;
  } while (iVar3 != 0xc);
  uVar2 = 0;
LAB:
  *out = uVar2;
}

