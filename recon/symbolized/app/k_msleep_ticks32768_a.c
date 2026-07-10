#include "g1_app_symbols.h"
/* named: k_msleep_ticks32768_a */
/* Reconstructed k_msleep_ticks32768_a @ 0x7cb8e  (parity: 300/300 trials, PROVEN) */

extern void __aeabi_uldivmod(int,int,int,int);
extern void thunk_FUN_00074844(void);
void k_msleep_ticks32768_a(int param_1)
{
  __aeabi_uldivmod(param_1 * 0x8000 + 999, param_1 >> 0x11, 1000, 0);
  thunk_FUN_00074844();
  return;
}

