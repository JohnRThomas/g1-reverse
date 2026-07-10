/* net-core FUN_01009118 @ 0x1009118  (parity 300 trials PROVEN) */

extern void FUN_0101f680(void);

unsigned int FUN_01009118(void)
{
  volatile unsigned char *p = (volatile unsigned char *)0x21000a30;
  if (p[0x2d] == 0 && p[0x2c] == 0) {
    FUN_0101f680();
    return 0;
  }
  return 0xffffffff;
}

