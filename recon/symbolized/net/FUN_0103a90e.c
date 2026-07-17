#include "g1_net_symbols.h"
/* net-core FUN_0103a90e @ 0x103a90e  (parity 300 trials PROVEN) */

extern unsigned long long FUN_01034508(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
extern unsigned int FUN_010344d4(unsigned int);
unsigned int FUN_0103a90e(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4) {
  unsigned int uVar1;
  unsigned long long uVar2;
  uVar2 = FUN_01034508(param_1, param_1, param_3, param_4, param_4);
  uVar1 = (unsigned int)uVar2;
  if (uVar1 != 0) {
    uVar1 = FUN_010344d4((unsigned int)(uVar2 >> 32));
  }
  return uVar1 & 1;
}
