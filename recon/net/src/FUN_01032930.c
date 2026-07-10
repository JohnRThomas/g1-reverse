/* net-core FUN_01032930 @ 0x1032930  (parity 300 trials PROVEN) */

extern unsigned long long FUN_0103a80c(unsigned int a, unsigned int b);

void FUN_01032930(void)
{
  unsigned int r4 = 0x2100068c;
  unsigned long long v;
  v = FUN_0103a80c(r4, 0x41008000);
  *(volatile unsigned int *)((unsigned int)(v >> 32) + 0x524) = (unsigned int)v;
  v = FUN_0103a80c(r4 + 4, 0x41008000);
  *(volatile unsigned int *)((unsigned int)(v >> 32) + 0x528) = (unsigned int)v;
}

