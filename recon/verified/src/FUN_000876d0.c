/* Reconstructed FUN_000876d0 @ 0x876d0  (parity: 300/300 trials, PROVEN) */

extern int FUN_00076e20(unsigned int, int, int, unsigned int, unsigned int);
extern void FUN_00086c78(int, int, int);

int FUN_000876d0(unsigned int param_1,int param_2,int param_3,unsigned int param_4)
{
  int iVar1;

  iVar1 = FUN_00076e20(param_1,param_3 * param_2,param_3,param_4,param_4);
  if (iVar1 != 0) {
    FUN_00086c78(iVar1,0,param_3 * param_2);
  }
  return iVar1;
}

