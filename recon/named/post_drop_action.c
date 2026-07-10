/* named: post_drop_action */
/* Reconstructed post_drop_action @ 0x7e4bc  (parity: 300/300 trials, PROVEN) */

extern long long idx_inc(int, int, int);

void post_drop_action(int *param_1, unsigned int param_2, int param_3)
{
  long long uVar2;
  int iVar1;
  uVar2 = idx_inc(0, 0, 0);
  iVar1 = (int)(uVar2 >> 32);
  if (*param_1 == (int)uVar2) {
    *param_1 = iVar1;
    param_1[4] = param_1[4] & 0xfffffff7;
  } else {
    *(unsigned int *)(param_1[8] + iVar1 * 4) = (param_3 << 2) | 2;
    iVar1 = (int)idx_inc((int)param_1, param_1[1], param_3);
    param_1[1] = iVar1;
  }
}

