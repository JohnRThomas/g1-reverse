/* net-core FUN_0102acb4 @ 0x102acb4  (parity 300 trials PROVEN) */

extern void FUN_01039722(unsigned int a);

unsigned int FUN_0102acb4(unsigned int param_1)
{
  *(unsigned int *)(param_1 + 0x60) = 0x0102b3ad;
  *(unsigned int *)(param_1 + 0x64) = 0x0102b351;
  *(volatile unsigned int *)0x21004604 = param_1;
  if (*(volatile int *)0x21000580 > 1) {
    FUN_01039722(0x0103cf0b);
  }
  return 0;
}

