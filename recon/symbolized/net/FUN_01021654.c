#include "g1_net_symbols.h"
/* net-core FUN_01021654 @ 0x1021654  (parity 300 trials PROVEN) */

extern int FUN_010209e0(int, unsigned int, int, int);
int FUN_01021654(int param_1,int param_2,int param_3,int param_4)
{
  unsigned int base = "%02X-0x%02X\n" /*=0x103c5c4*/;
  unsigned short h = *(unsigned short*)(base + param_2*2);
  int w = *(int*)(base + param_3*4 + 0x14);
  long long lVar1 = (unsigned long long)0x10624dd3u *
      (unsigned long long)(unsigned int)(param_1*1000 + w + (unsigned int)h + 2999);
  int iVar2 = FUN_010209e0(param_3, 0x10624dd3, param_3, (int)lVar1);
  return iVar2 + (unsigned int)((unsigned long long)lVar1 >> 0x26) + param_4 + 5;
}

