/* net-core FUN_0101e96c @ 0x101e96c  (parity 300 trials PROVEN) */

static volatile unsigned char * const DAT_0101e97c = (volatile unsigned char *)0x21000eac;
unsigned int FUN_0101e96c(unsigned short *param_1)
{
  unsigned short h = *(volatile unsigned short *)(DAT_0101e97c + 2);
  *param_1 = h;
  unsigned char b = DAT_0101e97c[0];
  *((unsigned char *)param_1 + 2) = b;
  return 0;
}

