/* named: font_glyph_pixel_offset */
/* Reconstructed font_glyph_pixel_offset @ 0x7d850  (parity: 300/300 trials, PROVEN) */

int font_glyph_pixel_offset(unsigned int param_1, unsigned int param_2, unsigned int param_3) {
  unsigned int a = param_1 - 0x20;
  unsigned short u = (unsigned short)a;
  if (u <= 0x5f) {
    return (int)(param_3 * param_2 * a);
  }
  return 0;
}

