/* net-core FUN_0100a6f0 @ 0x100a6f0  (parity 300 trials PROVEN) */

extern void FUN_010273c6(unsigned int a, unsigned int b, unsigned int c);
void FUN_0100a6f0(unsigned int param_1)
{
  volatile unsigned int *p1 = (volatile unsigned int *)0x21000bec;
  volatile unsigned int *p2 = (volatile unsigned int *)0x21000bf0;
  FUN_010273c6(*p1, param_1, *p2);
  return;
}

