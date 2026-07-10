/* Reconstructed FUN_00063570 @ 0x63570  (parity: 300/300 trials, PROVEN) */

extern void FUN_0007e2fa(int a, int b, int c, int d, int e);
extern unsigned int FUN_0007e2ec(int a, int b);
unsigned int FUN_00063570(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  unsigned int idx = param_1;
  if (1 < param_1) {
    FUN_0007e2fa(0x00099cbdUL, 0x000f668aUL, 0x000f6659UL, 0x86, param_4);
    idx = FUN_0007e2ec(0x000f6659UL, 0x86);
  }
  return 0x50015140UL + idx * 4;
}

