/* Reconstructed FUN_0005e9d0 @ 0x5e9d0  (parity: 300/300 trials, PROVEN) */

extern int FUN_0007e2fa(int a,int b,int c,int d,int e);
extern void FUN_0007e2ec(int a,int b);
extern int FUN_0005e7c8(void);
extern int FUN_0005e6a8(int a,int b);
extern void FUN_0005e9a0(int a,int b);
int FUN_0005e9d0(int param_1,int param_2,int param_3,int param_4)
{
  int iVar1;
  if (param_3 == 0) {
    FUN_0007e2fa(0x99cbd,0xf52ac,0xf5268,0xd2,param_4);
    FUN_0007e2ec(0xf5268,0xd2);
  }
  iVar1 = FUN_0005e7c8();
  if (iVar1 == 0 && (iVar1 = FUN_0005e6a8(param_2,param_3), iVar1 != 0)) {
    FUN_0005e9a0(iVar1,param_1);
  }
  return iVar1;
}

