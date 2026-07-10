/* Reconstructed FUN_00085020 @ 0x85020  (parity: 300/300 trials, PROVEN) */

int FUN_00085020(int *param_1)
{
  int *piVar1;
  int cnt;
  if (param_1 != 0) {
    piVar1 = (int *)*(int *)((char *)param_1 + 8);
    cnt = 0;
    while (piVar1 != (int *)0) {
      cnt = cnt + 1;
      piVar1 = (int *)*piVar1;
    }
    return cnt;
  }
  return 0;
}

