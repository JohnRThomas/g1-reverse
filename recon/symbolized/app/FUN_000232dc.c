#include "g1_app_symbols.h"
/* named: FUN_000232dc */
/* globals referenced:
//   0x20002fe3  g_product_code_buf           
*/
/* Reconstructed FUN_000232dc @ 0x232dc  (parity: 300/300 trials, PROVEN) */

extern unsigned int FUN_00077914(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
unsigned int FUN_000232dc(unsigned int param_1,unsigned int param_2,unsigned int param_3,unsigned int param_4)
{
  FUN_00077914(((uintptr_t)&g_product_code_buf) /*=0x20002fe3*/, 0x10, "%s" /*=0xa8c37*/, param_1, param_4);
  return 0;
}

