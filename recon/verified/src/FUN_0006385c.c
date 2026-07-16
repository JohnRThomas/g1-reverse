/* Reconstructed FUN_0006385c @ 0x6385c  (parity: 300/300 trials, PROVEN) */

unsigned int FUN_0006385c(void)
{
  volatile unsigned int *addr = (volatile unsigned int *)0x2000b2d4UL;
  unsigned int val, idx, old;
  while (1) {
    val = *addr;
    if (val == 0) return 0xfffffff4;
    idx = 31 - __builtin_clz(val);
    old = __atomic_fetch_and(addr, ~(1u << (idx & 0xff)),
                             __ATOMIC_ACQ_REL);
    if ((int)((old >> (idx & 0xff)) << 0x1f) < 0) break;
  }
  return idx;
}
