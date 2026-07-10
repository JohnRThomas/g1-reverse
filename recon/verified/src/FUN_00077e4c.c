/* Reconstructed FUN_00077e4c @ 0x77e4c  (parity: 300/300 trials, PROVEN) */

extern int FUN_000807e8(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);

void FUN_00077e4c(int *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  volatile int *piVar1;
  int iVar2;

  piVar1 = (volatile int *)0x2000cc24UL;
  *piVar1 = 0;
  iVar2 = FUN_000807e8(param_2,param_3,param_3,0,param_4);
  if ((iVar2 == -1) && (*piVar1 != 0)) {
    *param_1 = *piVar1;
  }
  return;
}

