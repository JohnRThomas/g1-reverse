/* net-core FUN_010246e4 @ 0x10246e4  (parity 300 trials PROVEN) */

extern void FUN_01024a9c(void);

void FUN_010246e4(void)
{
  unsigned int primask;
  __asm__ volatile("mrs %0, primask" : "=r"(primask));
  __asm__ volatile("cpsid i" ::: "memory");
  volatile unsigned char *base = (volatile unsigned char *)0x21001bd0;
  base[6] = base[6] + 1;
  if (base[6] == 1) {
    FUN_01024a9c();
  }
  if (primask == 0) {
    __asm__ volatile("cpsie i" ::: "memory");
  }
  return;
}

