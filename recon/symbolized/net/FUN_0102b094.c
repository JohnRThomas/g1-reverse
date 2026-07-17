#include "g1_net_symbols.h"
/* net-core FUN_0102b094 @ 0x102b094  (parity 300 trials PROVEN) */

extern void FUN_01039138(void *a, unsigned int b, unsigned int c, unsigned int d, unsigned int e,
                          unsigned int f, unsigned int g, unsigned int h, unsigned int i);
extern void FUN_01039722(unsigned int a, void *b);

unsigned int FUN_0102b094(unsigned char *param_1)
{
  volatile unsigned char *base = (volatile unsigned char *)0x01ff0000;
  unsigned int uVar1, uVar2, uVar3;
  unsigned char auStack_2c[20];

  if (*(volatile int *)(base + 0x2a4) == -1 &&
      (*(volatile unsigned int *)(base + 0x2a8) & 0xffff) == 0xffff) {
    uVar1 = 0;
  } else {
    uVar1 = *(volatile unsigned int *)(base + 0x2a0) & 1;
    if (uVar1 != 0) {
      uVar1 = *(volatile unsigned int *)(base + 0x2a4);
      uVar2 = *(volatile unsigned int *)(base + 0x2a8);
      uVar3 = ((uVar2 << 0x10) >> 0x18) | 0xc0;
      param_1[1] = (unsigned char)(uVar1 >> 8);
      param_1[3] = (unsigned char)(uVar1 >> 0x18);
      param_1[5] = (unsigned char)uVar3;
      param_1[0] = (unsigned char)uVar1;
      param_1[2] = (unsigned char)(uVar1 >> 0x10);
      param_1[4] = (unsigned char)uVar2;
      FUN_01039138(auStack_2c, 0x12, ((unsigned long)&rodata_103d0db) /*=0x103d0db*/, uVar3, uVar2 & 0xff, uVar1 >> 0x18,
                   (uVar1 << 8) >> 0x18, (uVar1 << 0x10) >> 0x18, uVar1 & 0xff);
      FUN_01039722(((unsigned long)&rodata_103d0f9) /*=0x103d0f9*/, auStack_2c);
      uVar1 = 1;
    }
  }
  return uVar1;
}
