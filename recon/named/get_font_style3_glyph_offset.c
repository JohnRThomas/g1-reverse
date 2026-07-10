/* named: get_font_style3_glyph_offset */
/* Reconstructed get_font_style3_glyph_offset @ 0x457f4  (parity: 300/300 trials, PROVEN) */

int get_font_style3_glyph_offset(unsigned int param_1, int *param_2, unsigned int *param_3)
{
  unsigned short *puVar6 = (unsigned short*)0x00098e3cUL;
  int iVar5 = 0;
  int iVar4 = 0;
  unsigned int val = 0;
  unsigned short key;
  int count = *(volatile int*)0x0008ac2cUL;
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
  return 0xe17da + iVar4;
}

