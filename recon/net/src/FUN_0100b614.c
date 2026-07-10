/* net-core FUN_0100b614 @ 0x100b614  (parity 300 trials PROVEN) */

volatile unsigned short *const DAT_0100b620 = (volatile unsigned short *)0x21000c48;
unsigned int FUN_0100b614(void)
{
  unsigned short v = *(volatile unsigned short *)((char*)DAT_0100b620 + 0x30);
  return ((unsigned int)v << 0x15) >> 0x1f;
}

