/* Reconstructed FUN_000369dc @ 0x369dc  (parity: 300/300 trials, PROVEN) */

void FUN_000369dc(unsigned int param_1)
{
  if (param_1 > 4) {
    param_1 = 0;
  }
  *(volatile unsigned char *)0x2001b811UL = 1;
  *(volatile unsigned char *)0x2001b810UL = (unsigned char)param_1;
}

