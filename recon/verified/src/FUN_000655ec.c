/* Reconstructed FUN_000655ec @ 0x655ec  (parity: 300/300 trials, PROVEN) */

extern int FUN_0007e2fa(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);
extern int FUN_0007e2ec(unsigned int a, unsigned int b);

int FUN_000655ec(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  unsigned int r0 = param_1;
  if (param_1 > 7) {
    FUN_0007e2fa(0x99cbd, 0xf6b73, 0xf6b3e, 0x2aa, param_4);
    r0 = FUN_0007e2ec(0xf6b3e, 0x2aa);
  }
  return r0 * 4 + 0x100;
}

