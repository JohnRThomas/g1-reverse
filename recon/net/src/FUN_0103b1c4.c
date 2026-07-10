/* net-core FUN_0103b1c4 @ 0x103b1c4  (parity 300 trials PROVEN) */
extern int FUN_01037670(int *, int);

int FUN_0103b1c4(int *param_1, int param_2)
{
  int iVar9 = (int)*(signed char *)((char *)param_1 + 0xe);
  if (iVar9 == param_2) {
    return 0;
  }
  return FUN_01037670(param_1, param_2);
}

