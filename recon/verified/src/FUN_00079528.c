/* Reconstructed FUN_00079528 @ 0x79528  (parity: 300/300 trials, PROVEN) */

extern int FUN_0004b088(unsigned int,unsigned int,unsigned int,unsigned int,unsigned int);
void FUN_00079528(int *param_1,unsigned int param_2,unsigned int param_3,unsigned int param_4)
{
  int *piVar1;
  int iVar2;
  piVar1 = (int*)0x2000cc24UL;
  *(volatile int*)0x2000cc24UL = 0;
  iVar2 = FUN_0004b088(param_2,param_3,param_4,param_4,param_4);
  if ((iVar2 == -1) && (*(volatile int*)piVar1 != 0)) {
    *param_1 = *(volatile int*)piVar1;
  }
  return;
}

