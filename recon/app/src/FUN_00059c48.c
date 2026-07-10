/* Reconstructed FUN_00059c48 @ 0x59c48  (parity: 300/300 trials, PROVEN) */

extern int FUN_000814e6(int a, unsigned char b);
extern int FUN_000826b2(unsigned char *a, int b);
unsigned char *FUN_00059c48(int param_1, unsigned char *param_2)
{
  int iVar1;

  if (param_1 == 0) {
    iVar1 = FUN_000826b2(param_2 + 1, 0x000f2b3a);
  } else {
    iVar1 = FUN_000814e6(param_1, *param_2);
  }
  if (iVar1 == 0) {
    param_2 = (unsigned char *)0;
  }
  return param_2;
}

