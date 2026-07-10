/* Reconstructed FUN_00085fd2 @ 0x85fd2  (parity: 300/300 trials, PROVEN) */

extern int FUN_00085da2(unsigned int *, unsigned int);
extern int FUN_00085e1a(unsigned int *, unsigned int, unsigned int, unsigned int);
extern void FUN_00085d70(unsigned int *, unsigned int);

unsigned int FUN_00085fd2(unsigned int *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  int iVar1;
  unsigned int uVar2;
  iVar1 = FUN_00085da2(param_1, 7);
  if (iVar1 != 0) {
    if ((*(unsigned char *)*param_1 & 0x1f) < 0x19) {
      uVar2 = FUN_00085e1a(param_1, param_2, 1, param_4);
      return uVar2;
    }
    FUN_00085d70(param_1, 10);
  }
  return 0;
}

