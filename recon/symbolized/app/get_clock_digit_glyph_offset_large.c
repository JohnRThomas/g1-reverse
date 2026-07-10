#include "g1_app_symbols.h"
/* named: get_clock_digit_glyph_offset_large */
/* Reconstructed get_clock_digit_glyph_offset_large @ 0x45764  (parity: 300/300 trials, PROVEN) */

int get_clock_digit_glyph_offset_large(unsigned int param_1, int *param_2, unsigned int *param_3)
{
  int iVar2 = 0;
  unsigned int uVar1 = 0;
  unsigned short *puVar3 = (unsigned short*)((uintptr_t)&tbl_98fbc) /*=0x98fe8*/;
  unsigned int key;
  unsigned char val = 0;
  while (1) {
    if (*(volatile int*)((uintptr_t)&tbl_8ac20) /*=0x8ac34*/ <= iVar2) {
      return 0;
    }
    key = *(volatile unsigned short*)puVar3;
    val = *(volatile unsigned char*)((char*)puVar3 + 2);
    puVar3 = puVar3 + 2;
    if (key == param_1) break;
    uVar1 = (uVar1 + (unsigned int)val * 0x27) & ((uintptr_t)&tbl_ffc8) /*=0xffff*/;
    iVar2 = iVar2 + 1;
  }
  *param_2 = (unsigned int)val << 1;
  *param_3 = 0x27;
  return ((uintptr_t)&rodata_e5248) /*=0xe5248*/ + uVar1;
}

