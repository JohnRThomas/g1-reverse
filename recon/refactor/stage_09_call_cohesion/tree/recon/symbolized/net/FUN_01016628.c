#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01016628 @ 0x01016628
 * public-name: FUN_01016628
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   controller_time_now                      <= FUN_01022f08 @ 0x01022f08
 */
/* net-core FUN_01016628 @ 0x1016628  (parity 300 trials PROVEN) */
#define P_010166bc G1N_21000f90

extern unsigned long long controller_time_now(void);
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
    cur = controller_time_now();
    deadline = *(volatile unsigned int *)(iVar2 + 0xa0) |
               ((unsigned long long)*(volatile unsigned int *)(iVar2 + 0xa4) << 32);
    if (cur >= deadline) {
      uVar3 = FUN_0100c738();
      lVar6 = controller_time_now();
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
