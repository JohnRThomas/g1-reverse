/* Reconstructed FUN_00037060 @ 0x37060  (parity: 300/300 trials, PROVEN) */

extern void FUN_0001672c(unsigned char);

unsigned char FUN_00037060(void)
{
  unsigned int base = 0x20004950UL;
  unsigned char value = *(volatile unsigned char *)0x2001b816UL;
  *(volatile unsigned char *)(base + 1) = value;
  FUN_0001672c(value);
  return *(volatile unsigned char *)(base + 1);
}
