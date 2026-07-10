/* Reconstructed FUN_000836de @ 0x836de  (parity: 300/300 trials, PROVEN) */

extern void FUN_0005eeb4(int a0, unsigned int a1);
void FUN_000836de(int param_1)
{
  unsigned int t1 = *(volatile unsigned int *)(param_1 + 0x2c);
  unsigned int t2 = *(volatile unsigned int *)(t1 + 4);
  unsigned int t3 = *(volatile unsigned int *)t2;
  FUN_0005eeb4(param_1, t3);
}

