/* Reconstructed FUN_0002360c @ 0x2360c  (parity: 300/300 trials, PROVEN) */

unsigned int FUN_0002360c(unsigned int param_1, unsigned char *param_2, int param_3)
{
  unsigned char *pbVar1;
  volatile unsigned int *tbl = (volatile unsigned int *)0x200075a0UL;
  param_1 = ~param_1;
  pbVar1 = param_2 + param_3;
  for (; param_2 != pbVar1; param_2 = param_2 + 1) {
    param_1 = tbl[(*param_2 ^ param_1) & 0xff] ^ (param_1 >> 8);
  }
  return ~param_1;
}

