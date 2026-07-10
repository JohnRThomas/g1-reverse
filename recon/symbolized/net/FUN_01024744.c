#include "g1_net_symbols.h"
/* net-core FUN_01024744 @ 0x1024744  (parity 300 trials PROVEN) */

extern void FUN_010246e4(void);
extern unsigned int FUN_01024ad0(void);

void FUN_01024744(void)
{
  unsigned int iVar1;
  unsigned int iVar2;
  unsigned int iVar3;

  FUN_010246e4();
  iVar3 = FUN_01024ad0();
  iVar2 = ((uintptr_t)&g_154_critical_section_nest_cnt) /*=0x21001bd0*/;
  iVar1 = REG_41005000 /*=0x41005000*/;
  if (iVar3 == 0) {
    *(volatile unsigned char *)(iVar2 + 0xd) = 3;
    *(volatile unsigned int *)(iVar1 + 0x304) = 1;
  } else {
    *(volatile unsigned int *)(iVar1 + 0x10) = 1;
    *(volatile unsigned char *)(iVar2 + 0xd) = 4;
  }
  *(volatile unsigned char *)(iVar2 + 0xe) = 0;
  return;
}

