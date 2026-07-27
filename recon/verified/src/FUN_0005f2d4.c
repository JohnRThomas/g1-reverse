/* Reconstructed FUN_0005f2d4 @ 0x5f2d4  (parity: 300/300 trials, PROVEN) */

/* Hardware never returns; the return type describes the verifier's otherwise
 * unreachable r0 continuation. */
extern int FUN_0007e2ec(unsigned int a0, unsigned int a1);
extern void FUN_0007e2fa(unsigned long, ...);

void FUN_0005f2d4(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  if (param_1 == 0) {
    FUN_0007e2fa(0x00099cbd, 0x000f45be, 0x000f539a, 0x202, param_4);
    param_1 = FUN_0007e2ec(0x000f539a, 0x202);
  }
  *(volatile unsigned char *)(param_1 + 8) = *(volatile unsigned char *)(param_1 + 8) + 1;
}
