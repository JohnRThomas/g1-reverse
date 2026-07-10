#include "g1_app_symbols.h"
/* named: l2cap_accept_no_ctx */
/* Reconstructed l2cap_accept_no_ctx @ 0x57438  (parity: 300/300 trials, PROVEN) */

extern void FUN_00081746(unsigned int a0, unsigned int a1, void *a2);

unsigned int l2cap_accept_no_ctx(unsigned int param_1)
{
  unsigned int local[3];
  local[0] = 3;
  local[1] = "No available L2CAP context for conn %p" /*=0xf3eea*/;
  local[2] = param_1;
  FUN_00081746(((uintptr_t)&tbl_880d8) /*=0x88160*/, 0x1840, local);
  return 0xfffffff4;
}

