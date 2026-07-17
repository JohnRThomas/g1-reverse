/* net-core FUN_01032764 @ 0x1032764  (parity 300 trials PROVEN) */

unsigned int FUN_01032764(void)
{
  volatile unsigned char *p8  = (volatile unsigned char*)0x21004a9c;
  volatile unsigned int  *p10 = (volatile unsigned int*)0x41008510;
  volatile unsigned int  *out = (volatile unsigned int*)0x210049a4;
  unsigned char bVar1 = *p8;

  *p10 = (unsigned int)bVar1;
  switch (bVar1) {
  case 0:
  case 3:
    *out = 300;
    return 1u;
  case 1:
  case 4:
    *out = 0xa0u;
    return 1u;
  default:
    return 0u;
  }
}
