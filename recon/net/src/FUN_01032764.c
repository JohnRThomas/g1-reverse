/* net-core FUN_01032764 @ 0x1032764  (parity 300 trials PROVEN) */

extern unsigned int FUN_z_oracle(void);

unsigned int FUN_01032764(void)
{
  volatile unsigned char *p8  = (volatile unsigned char*)0x21004a9c;
  volatile unsigned int  *p10 = (volatile unsigned int*)0x41008510;
  volatile unsigned int  *out = (volatile unsigned int*)0x210049a4;
  unsigned char bVar1 = *p8;

  *p10 = (unsigned int)bVar1;
  if (bVar1 == 1 || bVar1 == 4) {
    *out = 0xa0;
    return 1;
  }
  return FUN_z_oracle();
}

