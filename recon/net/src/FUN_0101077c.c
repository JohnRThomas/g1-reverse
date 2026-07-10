/* net-core FUN_0101077c @ 0x101077c  (parity 37 trials PROVEN) */

extern int FUN_01008d00(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);
extern int FUN_0101077c_after(void);

int FUN_0101077c(unsigned int param_1, int param_2, unsigned int param_3, unsigned int param_4)
{
  unsigned int r2 = param_1 & 7;
  if (r2 != 0) {
    FUN_01008d00(0x48, 99, r2, param_4, param_4);
    for (;;) {
      FUN_0101077c_after();
    }
  }
  if (param_1 != 0) {
    volatile unsigned char *p = (volatile unsigned char *)0x21000f14;
    p[8] = (unsigned char)param_2;
    *(volatile unsigned int *)(p + 4) = param_1;
    *p = (unsigned char)r2;
  }
  return param_2 << 3;
}

