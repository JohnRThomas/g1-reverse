/* net-core FUN_010209b8 @ 0x10209b8  (parity 300 trials PROVEN) */

volatile unsigned char *const DAT_010209c4 = (volatile unsigned char *)0x4100c000;
void FUN_010209b8(void)
{
  *(volatile unsigned int *)(DAT_010209c4 + 0x540) = 0;
}

