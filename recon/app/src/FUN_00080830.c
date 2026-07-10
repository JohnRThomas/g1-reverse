/* Reconstructed FUN_00080830 @ 0x80830  (parity: 300/300 trials, PROVEN) */

extern void FUN_0005ee6c(unsigned int);
extern int FUN_00083730(int *);
extern void thunk_FUN_00085cf2(int *, int, int, int, int, int, unsigned int);

void FUN_00080830(int *param_1, unsigned int param_2, unsigned int param_3)
{
  int uVar1;
  int iVar2;
  unsigned int iVar3;
  iVar3 = param_2;
  FUN_0005ee6c(param_2);
  *param_1 = param_2;
  *(unsigned short *)(param_2 + 0x10) = 8;
  iVar2 = *(int *)(param_2 + 0xc);
  uVar1 = FUN_00083730((int *)(param_2 + 0xc));
  thunk_FUN_00085cf2(param_1 + 1, 2, iVar2 + 8, uVar1, 0, iVar3, param_3);
}

