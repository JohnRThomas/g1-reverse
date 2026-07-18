#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00047ab8 @ 0x00047ab8
 * public-name: FUN_00047ab8
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   free                                     <= FUN_00076d7c @ 0x00076d7c
 * address symbols (name @ address):
 *   g_pixel4bit_row_buf                      @ 0x20009fcc
 */
/* Reconstructed FUN_00047ab8 @ 0x47ab8  (parity: 300/300 trials, PROVEN) */

extern void free(unsigned int);

void FUN_00047ab8(void)
{
  volatile int *piVar1 = (volatile int *)((unsigned long)&g_pixel4bit_row_buf) /*=0x20009fcc*/;
  int value = *piVar1;
  if (value != 0) {
    free((unsigned int)value);
    *piVar1 = 0;
  }
}
