/* Reconstructed FUN_0007e4bc @ 0x7e4bc  (parity: 300/300 trials, PROVEN) */

extern long long FUN_0007e35c(int, int, int);

void FUN_0007e4bc(int *param_1, unsigned int param_2, int param_3)
{
  long long uVar2;
  int iVar1;
  uVar2 = FUN_0007e35c(0, 0, 0);
  iVar1 = (int)(uVar2 >> 32);
  if (*param_1 == (int)uVar2) {
    *param_1 = iVar1;
    param_1[4] = param_1[4] & 0xfffffff7;
  } else {
    *(unsigned int *)(param_1[8] + iVar1 * 4) = (param_3 << 2) | 2;
    iVar1 = (int)FUN_0007e35c((int)param_1, param_1[1], param_3);
    param_1[1] = iVar1;
  }
}

