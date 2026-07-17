#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000457f4 @ 0x000457f4
 * public-name: get_font_style3_glyph_offset
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_font_style3_glyph_offset             <= FUN_000457f4 @ 0x000457f4
 * address symbols (name @ address):
 *   rodata_8ac2c                             @ 0x0008ac2c
 *   rodata_98e3c                             @ 0x00098e3c
 *   rodata_e17da                             @ 0x000e17da
 */
/* Reconstructed FUN_000457f4 @ 0x457f4  (parity: 300/300 trials, PROVEN) */

int get_font_style3_glyph_offset(unsigned int param_1, int *param_2, unsigned int *param_3)
{
  unsigned short *puVar6 = (unsigned short*)((unsigned long)&rodata_98e3c) /*=0x98e3c*/;
  int iVar5 = 0;
  int iVar4 = 0;
  unsigned int val = 0;
  unsigned short key;
  int count = *(volatile int*)((unsigned long)&rodata_8ac2c) /*=0x8ac2c*/;
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
  return ((unsigned long)&rodata_e17da) /*=0xe17da*/ + iVar4;
}
