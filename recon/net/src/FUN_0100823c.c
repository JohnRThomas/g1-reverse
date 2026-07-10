/* net-core FUN_0100823c @ 0x100823c  (parity 300 trials PROVEN) */

extern unsigned long long FUN_01025d38(int,int,int,int);
unsigned long long FUN_0100823c(int param_1,int param_2,int param_3,int param_4)
{
  if (param_4 == 0 && param_3 == 0) {
    if (param_2 != 0 || param_1 != 0) {
      param_2 = -1;
      param_1 = -1;
    }
    return ((unsigned long long)(unsigned int)param_2 << 32) | (unsigned int)param_1;
  }
  return FUN_01025d38(param_1,param_2,param_3,param_4);
}

