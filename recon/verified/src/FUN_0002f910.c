/* Reconstructed FUN_0002f910 @ 0x2f910  (parity: 300/300 trials, PROVEN) */

unsigned int FUN_0002f910(unsigned int param_1)
{
  volatile unsigned int *p = (volatile unsigned int *)0x20007bb0UL;
  unsigned int old = *p;
  *p = param_1;
  return old;
}

