/* Reconstructed FUN_0007fc2c @ 0x7fc2c  (parity: 300/300 trials, PROVEN) */

extern int FUN_0007fb20(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
extern int FUN_0007f97c(unsigned int, unsigned int, void*, unsigned int);

int FUN_0007fc2c(unsigned int param_1, unsigned char *param_2, unsigned int param_3, unsigned int param_4)
{
  int iVar1;
  int iVar2 = 0;
  unsigned char local_14;
  unsigned int uVar3;

  iVar1 = FUN_0007fb20(param_1, 2, param_3, param_4, param_1);
  if (iVar1 == 0) {
    iVar2 = FUN_0007f97c(param_1, 0x5f, &local_14, 1);
    if (iVar2 == 0) {
      uVar3 = (local_14 >> 3) & 3;
      if (uVar3==2 || uVar3==3 || uVar3==1) {
        *param_2 = (unsigned char)uVar3;
      } else {
        *param_2 = 0;
      }
    }
    iVar1 = FUN_0007fb20(param_1, 0, 0, 0, 0);
    iVar1 = iVar1 + iVar2;
  }
  return iVar1;
}

