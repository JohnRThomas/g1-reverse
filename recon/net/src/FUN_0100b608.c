/* net-core FUN_0100b608 @ 0x100b608  (parity 300 trials PROVEN) */

volatile unsigned char *DAT_0100b610 = (volatile unsigned char *)0x21000c48;
unsigned char FUN_0100b608(void)
{
  return DAT_0100b610[0xb0];
}

