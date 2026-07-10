/* Reconstructed FUN_0002bd4c @ 0x2bd4c  (parity: 300/300 trials, PROVEN) */

extern int FUN_0002bcbc(unsigned int a, unsigned int b, unsigned int c, unsigned int d);
extern int FUN_0002bc2c(unsigned int a, unsigned int b, unsigned int c);

unsigned int FUN_0002bd4c(unsigned int param_1, unsigned int param_2, int param_3, unsigned int param_4)
{
  unsigned int uVar1;
  if (param_3 != 0) {
    FUN_0002bcbc(param_1, param_2, 1, param_4);
    uVar1 = 0xa24e4;
  } else {
    FUN_0002bcbc(param_1, param_2, 0, param_4);
    uVar1 = 0xa24dc;
  }
  FUN_0002bc2c(uVar1, param_2, param_3 != 0);
  return 0;
}

