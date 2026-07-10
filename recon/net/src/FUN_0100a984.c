/* net-core FUN_0100a984 @ 0x100a984  (parity 300 trials PROVEN) */

unsigned int FUN_0100a984(void)
{
  volatile unsigned short *p34 = (volatile unsigned short *)0x21000c2c;
  volatile unsigned short *p38 = (volatile unsigned short *)0x21000c30;
  volatile unsigned char  *p32 = (volatile unsigned char  *)0x21000c2a;

  if (*p34 == *p38) {
    *p34 = 0xffff;
    if (*p32 != 0) {
      *p32 = 0;
      return 1;
    }
  }
  return 0;
}

