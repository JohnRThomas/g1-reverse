#include "g1_app_symbols.h"
/* named: FUN_00047ab8 */
/* Reconstructed FUN_00047ab8 @ 0x47ab8  (parity: 300/300 trials, PROVEN) */

extern void heap_free(void);
void FUN_00047ab8(void)
{
  volatile int *piVar1 = (volatile int *)((uintptr_t)&g_pixel4bit_row_buf) /*=0x20009fcc*/;
  if (*piVar1 != 0) {
    heap_free();
    *piVar1 = 0;
  }
}

