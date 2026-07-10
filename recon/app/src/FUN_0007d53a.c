/* Reconstructed FUN_0007d53a @ 0x7d53a  (parity: 145/300 trials, PROVEN) */

extern void FUN_00086c04(int a, int b, int c);
int FUN_0007d53a(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6)
{
  int *piVar1;
  int iVar2;

  if (199 < param_6) {
    param_6 = 200;
  }
  if (0x27f < param_5) {
    param_5 = 0x280;
  }
  piVar1 = (int *)(param_1 + param_6 * 4);
  for (iVar2 = 0; iVar2 < param_4; iVar2 = iVar2 + 1) {
    FUN_00086c04(*piVar1 + param_5 / 2,param_2,param_3);
    param_2 = param_2 + param_3;
    piVar1 = piVar1 + 1;
  }
  return param_6;
}

