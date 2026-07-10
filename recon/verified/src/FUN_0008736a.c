/* Reconstructed FUN_0008736a @ 0x8736a  (parity: 300/300 trials, PROVEN) */

void FUN_0008736a(unsigned int *param_1, unsigned int *param_2, int param_3)
{
  unsigned int *puVar1;
  unsigned int lshift = (unsigned int)(((8 - param_3) * -4) + 0x20) & 0xff;
  unsigned int rshift = (unsigned int)((8 - param_3) * 4) & 0xff;
  do {
    puVar1 = param_1 + 1;
    *param_1 = *param_1 | (*puVar1 << lshift);
    param_1 = param_1 + 1;
    *param_1 = *puVar1 >> rshift;
  } while (param_1 < param_2);
}

