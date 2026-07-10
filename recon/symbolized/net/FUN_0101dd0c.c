#include "g1_net_symbols.h"
/* net-core FUN_0101dd0c @ 0x101dd0c  (parity 300 trials PROVEN) */

void FUN_0101dd0c(int *param_1)
{
  int *base = (int*)param_1;
  int iVar3 = *(int*)((char*)base + 0x1c);
  int iVar2;
  if (iVar3 == 0) {
    iVar2 = *(int*)((char*)base + 0x18);
    *(int*)((uintptr_t)&g_timeout_list) /*=0x2100113c*/ = iVar2;
    if (iVar2 == 0) goto tail;
  } else {
    int iVar1 = *(int*)((char*)base + 8);
    int iVar4 = *(int*)((char*)base + 0xc);
    *(int*)(iVar3 + 0x18) = *(int*)((char*)base + 0x18);
    iVar2 = *(int*)((char*)base + 0x18);
    *(int*)(iVar3 + 0xc) = iVar1 + iVar4 + *(int*)(iVar3 + 0xc);
    if (iVar2 == 0) {
      *(int*)(iVar3 + 0xc) = 0;
      goto tail;
    }
  }
  *(int*)(iVar2 + 0x1c) = iVar3;
tail:
  *(int*)((char*)base + 0x18) = 0;
  *(int*)((char*)base + 0x1c) = 0;
}

