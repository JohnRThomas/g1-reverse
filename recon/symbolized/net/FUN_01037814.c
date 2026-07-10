#include "g1_net_symbols.h"
/* net-core FUN_01037814 @ 0x1037814  (parity 300 trials PROVEN) */

extern void FUN_01039bbe(unsigned int, unsigned int, unsigned int);
extern unsigned int FUN_01039bb0(unsigned int, unsigned int);
extern void FUN_0103735c(unsigned int, int*);
void FUN_01037814(int *param_1)
{
  unsigned int r0 = *(unsigned int*)((char*)param_1+8);
  if (r0 == 0) {
    FUN_01039bbe("acking error (context area might be not valid)" /*=0x103d2a7*/, ((uintptr_t)&rodata_103eb0e) /*=0x103eb0e*/, 0x2d2);
    r0 = FUN_01039bb0(((uintptr_t)&rodata_103eb0e) /*=0x103eb0e*/, 0x2d2);
  }
  FUN_0103735c(r0, param_1);
  *(unsigned char*)((char*)param_1+0xd) &= 0xfd;
  *(unsigned int*)((char*)param_1+8) = 0;
}

