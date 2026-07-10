/* Reconstructed FUN_0002eb28 @ 0x2eb28  (parity: 300/300 trials, PROVEN) */

void FUN_0002eb28(unsigned int param_1,int param_2)
{
  if (param_1 < 3) {
    if (param_2 != 0) {
      *(volatile unsigned char *)(0x20018da6UL + param_1) = 1;
      return;
    }
    *(volatile unsigned char *)(0x20018da6UL + param_1) = 0;
  }
}

