/* Reconstructed FUN_0007fe72 @ 0x7fe72  (parity: 300/300 trials, PROVEN) */

extern int FUN_0007f97c(int, int, void*, int);
extern int FUN_0007fb20(int, int, ...);

int FUN_0007fe72(int param_1, unsigned char *param_2, int param_3, int param_4)
{
  int iVar1, iVar2;
  int dummy;
  iVar1 = FUN_0007fb20(param_1, 1, param_3, param_4, param_1);
  if (iVar1 == 0) {
    iVar1 = FUN_0007f97c(param_1, 0x14, &dummy, 1);
    *param_2 = (unsigned char)(((unsigned int)(unsigned long)param_2 >> 2) & 1);
    iVar2 = FUN_0007fb20(param_1, 0);
    iVar1 = iVar1 + iVar2;
  }
  return iVar1;
}

