#include "g1_app_symbols.h"
/* named: FUN_0007c0a8 */
/* Reconstructed FUN_0007c0a8 @ 0x7c0a8  (parity: 300/300 trials, PROVEN) */

extern void __aeabi_uldivmod(int,int,int,int);
extern void thunk_FUN_00074844(void);
void FUN_0007c0a8(int param_1)
{
  __aeabi_uldivmod(param_1 * 0x8000 + 999, param_1 >> 0x11, 1000, 0);
  thunk_FUN_00074844();
  return;
}

