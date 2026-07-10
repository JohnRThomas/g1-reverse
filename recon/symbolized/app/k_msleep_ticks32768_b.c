#include "g1_app_symbols.h"
/* named: k_msleep_ticks32768_b */
/* Reconstructed k_msleep_ticks32768_b @ 0x7d14a  (parity: 300/300 trials, PROVEN) */

extern void __aeabi_uldivmod(int,int,int,int);
extern void FUN_00074844(void);
void k_msleep_ticks32768_b(int param_1)
{
  __aeabi_uldivmod(param_1 * 0x8000 + 999, param_1 >> 0x11, 1000, 0);
  FUN_00074844();
  return;
}

