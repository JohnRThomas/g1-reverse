/* readable reconstruction; identity: FUN_00045840 @ 0x00045840
 * public-name: get_default_font_glyph_offset
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_default_font_glyph_offset            <= FUN_00045840 @ 0x00045840
 * address symbols (name @ address):
 *   g_default_font_glyph_table_count         @ 0x0008ac28
 *   rodata_9890c                             @ 0x0009890c
 *   rodata_e5f62                             @ 0x000e5f62
 */
/* Reconstructed FUN_00045840 @ 0x45840  (parity: 300/300 trials, PROVEN) */

int get_default_font_glyph_offset(unsigned int param_1, int *param_2, unsigned int *param_3)
{
  int iVar2 = 0;
  unsigned int uVar1 = 0;
  unsigned short *puVar3 = (unsigned short*)0x0009890cUL;
  unsigned int key;
  unsigned char val = 0;
  while (1) {
    if (*(volatile int*)0x0008ac28UL <= iVar2) {
      return 0;
    }
    key = *(volatile unsigned short*)puVar3;
    val = *(volatile unsigned char*)((char*)puVar3 + 2);
    puVar3 = puVar3 + 2;
    if (key == param_1) break;
    uVar1 = (uVar1 + (unsigned int)val * 0x1a) & 0xffff;
    iVar2 = iVar2 + 1;
  }
  *param_2 = (unsigned int)val << 1;
  *param_3 = 0x1a;
  return 0xe5f62 + uVar1;
}
