/* Reconstructed FUN_0005f304 @ 0x5f304  (parity: 300/300 trials, PROVEN) */

extern int FUN_0007e2fa(unsigned int a,unsigned int b,unsigned int c,unsigned int d,unsigned int e);
extern int FUN_0007e2ec(unsigned int a,unsigned int b);

int FUN_0005f304(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  int iVar1;
  if (param_1 == 0) {
    FUN_0007e2fa(0x99cbd, 0xf45be, 0xf539a, 0x236, param_4);
    FUN_0007e2ec(0xf539a, 0x236);
  }
  do {
    iVar1 = param_1;
    param_1 = *(int*)(param_1+4);
  } while (param_1 != 0);
  return iVar1;
}

