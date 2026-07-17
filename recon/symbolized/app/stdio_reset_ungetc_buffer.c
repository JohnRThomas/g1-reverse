#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00087862 @ 0x00087862
 * public-name: stdio_reset_ungetc_buffer
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   heap_free_core                           <= FUN_00076d8c @ 0x00076d8c
 *   stdio_reset_ungetc_buffer                <= FUN_00087862 @ 0x00087862
 */
/* Reconstructed FUN_00087862 @ 0x87862  (parity: 300/300 trials, PROVEN) */

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
