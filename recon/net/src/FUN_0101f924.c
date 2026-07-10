/* net-core FUN_0101f924 @ 0x101f924  (parity 300 trials PROVEN) */

volatile unsigned char *const DAT_0101f930 = (volatile unsigned char *)0x2100144a;
unsigned char FUN_0101f924(void)
{
  return *DAT_0101f930 & 7;
}

