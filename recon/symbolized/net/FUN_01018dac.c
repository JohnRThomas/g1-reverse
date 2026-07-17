#include "g1_net_symbols.h"
/* net-core FUN_01018dac @ 0x1018dac  (parity 300 trials PROVEN) */

extern unsigned int FUN_0100a5a0(void);
extern unsigned int FUN_0100a5b4(void);
extern unsigned int FUN_01026e48(unsigned int, unsigned short);
extern void FUN_01008d00(int,int) __attribute__((noreturn));
void FUN_01018dac(unsigned int param_1)
{
  unsigned int uVar2 = FUN_0100a5a0();
  unsigned short uVar1 = (unsigned short)FUN_0100a5b4();
  unsigned int iVar3 = FUN_01026e48(uVar2, uVar1);
  if (iVar3 != 0) {
    void **p = *(void***)(0x21000f90 + 0xc4);
    void (*fn)(unsigned int, unsigned int) = (void(*)(unsigned int,unsigned int))*p;
    fn(param_1, iVar3);
    return;
  }
  FUN_01008d00(0x32, 0xaa5);
  __builtin_unreachable();
}
