/* Reconstructed FUN_00085ebc @ 0x85ebc  (parity: 300/300 trials, PROVEN) */

extern int FUN_00085da2(int *, unsigned int, unsigned int, unsigned int, unsigned int);
extern int FUN_00085e1a(int *, int *);
extern void FUN_00085dc4(int *, int);

int FUN_00085ebc(int *param_1, int *param_2, unsigned int param_3, unsigned int param_4)
{
  int iVar1;
  int iVar2;
  iVar1 = FUN_00085da2(param_1, param_3, param_3, param_4, param_4);
  if (iVar1 != 0) {
    iVar1 = FUN_00085e1a(param_1, param_2 + 1);
    if (iVar1 != 0) {
      iVar2 = *param_1;
      *param_2 = iVar2;
      if ((unsigned int)param_2[1] <= (unsigned int)(param_1[3] - iVar2)) {
        return iVar1;
      }
      FUN_00085dc4(param_1, 8);
    }
  }
  return 0;
}

