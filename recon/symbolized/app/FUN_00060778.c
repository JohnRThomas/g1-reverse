#include "g1_app_symbols.h"
/* named: FUN_00060778 */
/* Reconstructed FUN_00060778 @ 0x60778  (parity: 300/300 trials, PROVEN) */

unsigned int FUN_00060778(unsigned int param_1)
{
  unsigned int b = param_1 & 0xffu;
  return ((uintptr_t)&g_dev_inst_data_pool) /*=0x2000b098*/ + (b << 5);
}

