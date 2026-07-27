/* Reconstructed FUN_0005e9a0 @ 0x5e9a0  (parity: 300/300 trials, PROVEN) */

extern unsigned long long FUN_0007e2ec(unsigned int a0, unsigned int a1);
extern void FUN_0007e2fa(unsigned long, ...);

void FUN_0005e9a0(int param_1, unsigned short param_2, unsigned int param_3, unsigned int param_4)
{
  if (param_1 == 0) {
    unsigned long long r;
    FUN_0007e2fa(0x00099cbd, 0x000f5298, 0x000f5268, 0x12a);
    r = FUN_0007e2ec(0x000f5268, 0x12a);
    param_1 = (int)r;
    param_2 = (unsigned short)(r >> 32);
  }
  *(volatile unsigned short *)(param_1 + 0xe) = param_2 | *(volatile unsigned short *)(param_1 + 0xe);
}
