/* Reconstructed FUN_000730b4 @ 0x730b4  (parity: 300/300 trials, PROVEN) */

extern int FUN_0007e2fa(unsigned int a, unsigned int b, unsigned int c, unsigned int d);
extern int FUN_0007e2ec(unsigned int a, unsigned int b);
extern void FUN_00086c78(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);

void FUN_000730b4(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  unsigned int r0 = (unsigned int)param_1;
  if (param_1 == 0) {
    FUN_0007e2fa(0x99cbd, 0xf824d, 0xf820f, 0x2b9);
    r0 = FUN_0007e2ec(0xf820f, 0x2b9);
  }
  FUN_00086c78(r0, 0, 0xf8, param_4, param_4);
}

