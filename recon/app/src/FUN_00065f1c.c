/* Reconstructed FUN_00065f1c @ 0x65f1c  (parity: 300/300 trials, PROVEN) */

extern void FUN_00065ef0(void);
extern void FUN_0007e2fa(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);
extern void FUN_0007e2ec(unsigned int a, unsigned int b);

unsigned int FUN_00065f1c(unsigned int *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  if ((unsigned int)param_1 >= 0x100000u) {
    FUN_0007e2fa(0x99cbd, 0xf6c8e, 0xf6c32, 0x107, param_4);
    FUN_0007e2ec(0xf6c32, 0x107);
    return 0x0bad000a;
  }
  if (((unsigned int)param_1 & 0xfff) != 0) {
    return 0x0bad000a;
  }
  *(volatile unsigned int *)(0x50039000UL + 0x584) = 2;
  *(volatile unsigned int *)(0x50039000UL + 0x504) = 2;
  *param_1 = 0xffffffff;
  while (((int)(*(volatile unsigned int *)(0x50039000UL + 0x400) << 0x1f)) >= 0) {}
  FUN_00065ef0();
  return 0x0bad0000;
}

