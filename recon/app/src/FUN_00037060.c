/* Reconstructed FUN_00037060 @ 0x37060  (parity: 300/300 trials, PROVEN) */

extern void FUN_0001672c(void);
unsigned char FUN_00037060(void)
{
  unsigned int base = 0x20004950UL;
  *(volatile unsigned char *)(base + 1) = *(volatile unsigned char *)0x2001b816UL;
  FUN_0001672c();
  return *(volatile unsigned char *)(base + 1);
}

