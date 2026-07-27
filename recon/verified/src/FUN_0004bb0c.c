/* Reconstructed FUN_0004bb0c @ 0x4bb0c  (parity: 300/300 trials, PROVEN) */

extern void FUN_000757b0(unsigned int, unsigned int);
extern void FUN_0007e2fa(unsigned long, ...);
extern void FUN_0007e2ec(unsigned int a, unsigned int b);
int FUN_0004bb0c(int *param_1,int param_2,unsigned int param_3,unsigned int param_4)
{
  unsigned int uVar1;
  int r0;
  uVar1 = param_1[1] & 3;
  param_1[2] = param_2;
  if (uVar1 == 2) {
    r0 = param_1[0];
    param_1[1] = 0;
    if (r0 != 0) {
      FUN_000757b0((unsigned int)r0, (unsigned int)param_2);
    }
    return 0;
  } else if (uVar1 == 3) {
    r0 = param_1[0];
    param_1[1] = 0;
    return r0;
  } else if (uVar1 == 1) {
    param_1[1] = 0;
    return 0;
  } else {
    FUN_0007e2fa(0x99cbd, 0xf7a30, 0xf0959, 0x45, param_4);
    FUN_0007e2ec(0xf0959, 0x45);
    FUN_000757b0(0xf0959, 0x45);
    return 0;
  }
}
