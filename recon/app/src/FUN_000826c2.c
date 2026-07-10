/* Reconstructed FUN_000826c2 @ 0x826c2  (parity: 300/300 trials, PROVEN) */

extern int FUN_000826b2(unsigned char *);

unsigned char * FUN_000826c2(unsigned char *param_1, unsigned int param_2, unsigned int param_3)
{
  int iVar1;

  if (*param_1 == param_3) {
    iVar1 = FUN_000826b2(param_1 + 1);
    if (iVar1 == 0) {
      param_1 = (unsigned char *)0x0;
    }
  }
  else {
    param_1 = (unsigned char *)0x0;
  }
  return param_1;
}

