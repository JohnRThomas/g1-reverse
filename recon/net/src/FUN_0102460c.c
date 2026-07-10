/* net-core FUN_0102460c @ 0x102460c  (parity 300 trials PROVEN) */

void FUN_0102460c(void)
{
  volatile signed char *p = (volatile signed char *)0x21001bca;
  int v = (int)*p;
  if (v >= 0) {
    volatile unsigned int *base = (volatile unsigned int *)0xe000e100;
    base[(v >> 5) + 0x40] = 1u << (v & 0x1f);
  }
  return;
}

