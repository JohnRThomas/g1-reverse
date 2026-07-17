#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00045764 @ 0x00045764
 * public-name: get_clock_digit_glyph_offset_large
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_clock_digit_glyph_offset_large       <= FUN_00045764 @ 0x00045764
 * address symbols (name @ address):
 *   rodata_8ac34                             @ 0x0008ac34
 *   rodata_98fe8                             @ 0x00098fe8
 *   rodata_e5248                             @ 0x000e5248
 */
/* Reconstructed FUN_00045764 @ 0x45764  (parity: 300/300 trials, PROVEN) */

int get_clock_digit_glyph_offset_large(unsigned int param_1, int *param_2, unsigned int *param_3)
{
  int iVar2 = 0;
  unsigned int uVar1 = 0;
  unsigned short *puVar3 = (unsigned short*)((unsigned long)&rodata_98fe8) /*=0x98fe8*/;
  unsigned int key;
  unsigned char val = 0;
  while (1) {
    if (*(volatile int*)((unsigned long)&rodata_8ac34) /*=0x8ac34*/ <= iVar2) {
      return 0;
    }
    key = *(volatile unsigned short*)puVar3;
    val = *(volatile unsigned char*)((char*)puVar3 + 2);
    puVar3 = puVar3 + 2;
    if (key == param_1) break;
    uVar1 = (uVar1 + (unsigned int)val * 0x27) & 0xffff;
    iVar2 = iVar2 + 1;
  }
  *param_2 = (unsigned int)val << 1;
  *param_3 = 0x27;
  return ((unsigned long)&rodata_e5248) /*=0xe5248*/ + uVar1;
}
