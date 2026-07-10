#include "g1_app_symbols.h"
/* named: get_font_style3_glyph_offset */
/* Reconstructed get_font_style3_glyph_offset @ 0x457f4  (parity: 300/300 trials, PROVEN) */

int get_font_style3_glyph_offset(unsigned int param_1, int *param_2, unsigned int *param_3)
{
  unsigned short *puVar6 = (unsigned short*)((uintptr_t)&tbl_98e3c) /*=0x98e3c*/;
  int iVar5 = 0;
  int iVar4 = 0;
  unsigned int val = 0;
  unsigned short key;
  int count = *(volatile int*)((uintptr_t)&tbl_8ac20) /*=0x8ac2c*/;
  while (1) {
    if (count <= iVar5) return 0;
    key = *(volatile unsigned short*)puVar6;
    val = *(volatile unsigned char*)((char*)puVar6 + 2);
    puVar6 = puVar6 + 2;
    if ((unsigned int)key == param_1) break;
    iVar4 = (int)(short)(unsigned short)val * 0x1a + iVar4;
    iVar5 = iVar5 + 1;
  }
  *param_2 = val << 1;
  *param_3 = 0x1a;
  return ((uintptr_t)&rodata_e17da) /*=0xe17da*/ + iVar4;
}

