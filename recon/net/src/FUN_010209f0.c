/* net-core FUN_010209f0 @ 0x10209f0  (parity 300 trials PROVEN) */

volatile unsigned int *const DAT_010209fc = (volatile unsigned int *)0x0103c4d0;
unsigned int FUN_010209f0(int param_1)
{
  return *(volatile unsigned int *)((char *)DAT_010209fc + param_1 * 4 + 0x70);
}

