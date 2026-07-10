#include "g1_net_symbols.h"
/* net-core FUN_0103b53a @ 0x103b53a  (parity 300 trials PROVEN) */

extern unsigned long long FUN_0102fa84(void);
extern void FUN_0103b614(void);

void FUN_0103b53a(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  unsigned long long uVar3;
  unsigned int uVar1, uVar2;

  uVar3 = ((unsigned long long)param_2 << 32) | param_1;
  if (param_3 <= param_4) goto LAB1;
  do {
    uVar3 = FUN_0102fa84();
LAB1:
    uVar2 = (unsigned int)(uVar3 >> 32);
    uVar1 = (unsigned int)uVar3;
    if (uVar2 <= uVar1) {
      if (uVar1 < uVar2 + param_3) continue;
      if (uVar2 != uVar1) break;
    }
    if (uVar1 + param_3 <= uVar2) break;
  } while (1);
  FUN_0103b614();
}

