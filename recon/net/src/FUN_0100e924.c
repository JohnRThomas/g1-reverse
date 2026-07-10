/* net-core FUN_0100e924 @ 0x100e924  (parity 300 trials PROVEN) */

static volatile unsigned char * const DAT_0100e930 = (volatile unsigned char *)0x21000eac;
unsigned char FUN_0100e924(void)
{
  return (unsigned char)((~DAT_0100e930[0x16]) & 1);
}

