#include "g1_net_symbols.h"
/* net-core FUN_0100d58c @ 0x100d58c  (parity 300 trials PROVEN) */

extern unsigned int FUN_01008d00(int,int,int,int,int);
unsigned int FUN_0100d58c(int param_1,unsigned int param_2,int param_3,int param_4)
{
  unsigned int uVar1;
  switch(param_2) {
    case 1: break;
    case 2: return 0x9c4;
    case 4:
    case 8:
      return 0xea6;
    default:
      return FUN_01008d00(0x29,0x270,param_3,param_4,param_4);
  }
  uVar1 = 0x9c4;
  if (param_1==0) uVar1=0x4e2;
  return uVar1;
}

