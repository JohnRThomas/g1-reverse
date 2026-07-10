#include "g1_app_symbols.h"
/* named: app_msleep_thunk_a */
/* Reconstructed app_msleep_thunk_a @ 0x7c038  (parity: 300/300 trials, PROVEN) */

extern void __aeabi_uldivmod(int,int,int,int);
extern void FUN_00074844(void);
void app_msleep_thunk_a(int param_1)
{
  __aeabi_uldivmod(param_1 * 0x8000 + 999, param_1 >> 0x11, 1000, 0);
  FUN_00074844();
  return;
}

