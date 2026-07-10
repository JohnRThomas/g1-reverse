#include "g1_app_symbols.h"
/* named: crc16_ansi */
/* Reconstructed crc16_ansi @ 0x7da4a  (parity: 300/300 trials, PROVEN) */

extern unsigned int crc16_reflect(unsigned int a,unsigned int b,unsigned int c,unsigned int d,unsigned int e,unsigned int f,unsigned int g,unsigned int h);

unsigned int crc16_ansi(unsigned int param_1, int param_2, int param_3, unsigned int param_4)
{
  unsigned int uVar1;
  if (param_2 == 0 || param_3 < 1) {
    uVar1 = 0;
  } else {
    uVar1 = crc16_reflect(param_1, 0x8005, ((uintptr_t)&tbl_ffc8) /*=0xffff*/, 1, 1, (unsigned int)param_2, (unsigned int)param_3, param_4);
  }
  return uVar1;
}

