/* named: stdio_reset_ungetc_buffer */
/* Reconstructed stdio_reset_ungetc_buffer @ 0x87862  (parity: 300/300 trials, PROVEN) */

extern void heap_free_core(void);
int stdio_reset_ungetc_buffer(int param_1, unsigned int *param_2)
{
  if (param_2[0xd] != 0) {
    if (param_2[0xd] != (unsigned int)(param_2 + 0x11)) {
      heap_free_core();
    }
    param_2[0xd] = 0;
    param_2[1] = param_2[0x10];
    if (param_2[0x10] != 0) {
      *param_2 = param_2[0xf];
      return 0;
    }
  }
  *param_2 = param_2[4];
  param_2[1] = 0;
  *(unsigned short *)((char*)param_2 + 0xc) |= 0x20;
  return -1;
}

