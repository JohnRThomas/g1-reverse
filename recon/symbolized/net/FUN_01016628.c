#include "g1_net_symbols.h"
/* net-core FUN_01016628 @ 0x1016628  (parity 300 trials PROVEN) */
#define P_010166bc 0x21000f90

extern unsigned long long FUN_01022f08(void);
extern unsigned int FUN_0100c738(void);
extern void FUN_0100cb70(int);

void FUN_01016628(void)
{
  int iVar2;
  unsigned char *pcVar1;
  unsigned long long cur;
  unsigned long long deadline;
  unsigned int uVar3;
  unsigned long long lVar6;
  unsigned long long newdl;
  unsigned int lo, hi;

  iVar2 = P_010166bc;
  pcVar1 = (unsigned char *)(iVar2 + 0x58);
  *(volatile unsigned char *)(iVar2 + 0xa8) = 0;
  if ((*pcVar1 != 0 || *(unsigned char *)(iVar2 + 0x7d) != 0) &&
      (*(int *)(iVar2 + 0xa4) != 0x7fffffff || *(int *)(iVar2 + 0xa0) != -1)) {
    cur = FUN_01022f08();
    deadline = *(volatile unsigned int *)(iVar2 + 0xa0) |
               ((unsigned long long)*(volatile unsigned int *)(iVar2 + 0xa4) << 32);
    if (cur >= deadline) {
      uVar3 = FUN_0100c738();
      lVar6 = FUN_01022f08();
      newdl = lVar6 + (unsigned long long)uVar3 * 1000000ULL;
      lo = (unsigned int)newdl;
      hi = (unsigned int)(newdl >> 32);
      *(volatile unsigned int *)(iVar2 + 0xa0) = lo;
      *(volatile unsigned int *)(iVar2 + 0xa4) = hi;
      if (*(unsigned char *)(iVar2 + 0x7d) != 0) {
        FUN_0100cb70(1);
      }
    }
  }
  *(volatile unsigned char *)(iVar2 + 0x70) = 2;
  return;
}
