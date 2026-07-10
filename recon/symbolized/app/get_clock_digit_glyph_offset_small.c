#include "g1_app_symbols.h"
/* named: get_clock_digit_glyph_offset_small */
/* Reconstructed get_clock_digit_glyph_offset_small @ 0x457b0  (parity: 300/300 trials, PROVEN) */

int get_clock_digit_glyph_offset_small(unsigned int param_1, int *param_2, unsigned int *param_3)
{
  unsigned int uVar1 = 0;
  int iVar2 = 0;
  volatile unsigned short *puVar3 = (volatile unsigned short *)((uintptr_t)&tbl_98fbc) /*=0x98fbc*/;
  int count = *(volatile int*)((uintptr_t)&tbl_8ac20) /*=0x8ac30*/;
  unsigned short id;
  unsigned char b;
  while (1) {
    if (count <= iVar2) return 0;
    id = puVar3[0];
    b = (unsigned char)puVar3[1];
    if (id == param_1) break;
    uVar1 = (uVar1 + ((unsigned int)b << 5)) & ((uintptr_t)&tbl_ffc8) /*=0xffff*/;
    iVar2 += 1;
    puVar3 += 2;
  }
  *param_2 = (unsigned int)b << 1;
  *param_3 = 0x20;
  return ((uintptr_t)&rodata_e4408) /*=0xe4408*/ + uVar1;
}

