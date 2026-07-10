#include "g1_app_symbols.h"
/* named: FUN_000527dc */
/* globals referenced:
//   0x20005cb0  g_active_transfer_conn       
*/
/* Reconstructed FUN_000527dc @ 0x527dc  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
int* FUN_000527dc(int param_1)
{
  volatile int *p = (volatile int*)((uintptr_t)&g_active_transfer_conn) /*=0x20005cb0*/;
  if (*p != param_1) {
    return (int*)0;
  }
  return (int*)p;
}

