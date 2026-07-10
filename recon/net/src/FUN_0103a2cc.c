/* net-core FUN_0103a2cc @ 0x103a2cc  (parity 300 trials PROVEN) */

extern void FUN_0103b614(unsigned int dst, unsigned int src, unsigned int len);

unsigned int FUN_0103a2cc(unsigned int param_1, unsigned int param_2, int *param_3)
{
  if ((unsigned int)(param_3[1] - param_3[2]) < param_2) {
    param_2 = 0xffffffe4;
  } else {
    FUN_0103b614((unsigned int)param_3[0] + (unsigned int)param_3[2], param_1, param_2);
    param_3[2] = param_3[2] + param_2;
  }
  return param_2;
}

