#include "g1_app_symbols.h"
/* named: FUN_00063ba8 */
/* Reconstructed FUN_00063ba8 @ 0x63ba8  (parity: 300/300 trials, PROVEN) */

unsigned int FUN_00063ba8(int param_1)
{
  int i = 0;
  while (1) {
    if (*(volatile int *)(((uintptr_t)&g_ancs_notify_slot_table) /*=0x2000b308*/ + i*4) != 0) {
      return 0;
    }
    if (!(param_1 > i)) {
      return 1;
    }
    i = i + 1;
  }
}

