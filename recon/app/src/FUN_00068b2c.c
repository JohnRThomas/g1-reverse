/* Reconstructed FUN_00068b2c @ 0x68b2c  (parity: 300/300 trials, PROVEN) */

extern void FUN_00068908(int,unsigned int,unsigned int);
void FUN_00068b2c(int param_1, unsigned int param_2, int param_3)
{
  unsigned int uVar1;
  int iVar2;
  uVar1 = (param_2 > 1) ? 1 : 0;
  if (param_2 != 0) uVar1 += 1;
  if (param_2 > 3) uVar1 += 1;
  if (uVar1 != 0) {
    iVar2 = uVar1 + *(unsigned int*)(param_1+0x20);
    if (iVar2 > 0x20) {
      FUN_00068908(param_1, (unsigned int)param_3, uVar1);
      return;
    }
    *(unsigned int*)(param_1+0x1c) = *(unsigned int*)(param_1+0x1c) | (param_3 << (*(unsigned int*)(param_1+0x20) & 0xff));
    *(int*)(param_1+0x20) = iVar2;
  }
}
