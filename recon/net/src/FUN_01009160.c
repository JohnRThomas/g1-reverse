/* net-core FUN_01009160 @ 0x1009160  (parity 300 trials PROVEN) */

extern void FUN_010294b4(void);

unsigned int FUN_01009160(void)
{
  volatile unsigned char *p = (volatile unsigned char *)0x21000a30;
  if (p[0x2d] == 0 && p[0x2c] == 0) {
    FUN_010294b4();
    return 0;
  }
  return 0xffffffff;
}

