/* named: memcpy */
/* Reconstructed memcpy @ 0x86c04  (parity: 300/300 trials, PROVEN) */

void memcpy(unsigned char *param_1, unsigned char *param_2, int param_3)
{
  unsigned char *end = param_2 + param_3;
  unsigned char *dst = param_1 - 1;
  if (param_2 != end) {
    do {
      unsigned char v = *(volatile unsigned char *)param_2;
      param_2 = param_2 + 1;
      dst = dst + 1;
      *(volatile unsigned char *)dst = v;
    } while (param_2 != end);
  }
}

