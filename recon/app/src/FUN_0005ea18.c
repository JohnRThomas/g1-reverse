/* Reconstructed FUN_0005ea18 @ 0x5ea18  (parity: 300/300 trials, PROVEN) */

extern void FUN_0007e2fa(int a,int b,int c,int d);
extern unsigned char *FUN_0007e2ec(int a,int b);
extern void FUN_00055094(void);
extern void FUN_00053184(unsigned char a, unsigned char *b);
extern void FUN_00086c78(void *a, int b, int c);

void FUN_0005ea18(unsigned char *param_1)
{
  unsigned char *r0 = param_1;
  if (param_1 == 0) {
    FUN_0007e2fa(0x00099cbd, 0x000f5298, 0x000f5268, 0x131);
    r0 = FUN_0007e2ec(0x000f5268, 0x131);
  }
  unsigned char b8 = *(volatile unsigned char*)(r0 + 8);
  if ((int)((unsigned int)b8 << 0x1d) < 0) {
    FUN_00055094();
  }
  FUN_00053184(*param_1, param_1 + 1);
  FUN_00086c78(param_1, 0, 0x5c);
}

