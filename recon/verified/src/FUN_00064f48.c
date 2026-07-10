/* Reconstructed FUN_00064f48 @ 0x64f48  (parity: 300/300 trials, PROVEN) */

extern void FUN_0007e2fa(int a, int b, int c, int d, int e);
extern unsigned int FUN_0007e2ec(int a, int b);
void FUN_00064f48(unsigned int param_1, int param_2, unsigned int param_3, unsigned int param_4)
{
  unsigned int val = param_1;
  if (param_2 == 0) {
    FUN_0007e2fa(0x000f6a46UL, 0x00099cbdUL, 0x000f6a09UL, 0x44, param_4);
    val = FUN_0007e2ec(0x000f6a09UL, 0x44);
  }
  *(volatile unsigned int *)(param_2 + 0x80) = val | 0x80000000UL;
}

