#include "g1_app_symbols.h"
/* named: get_elapsed_ms_since_mark */
/* globals referenced:
//   0x20007a28  g_elapsed_time_mark          
*/
/* Reconstructed get_elapsed_ms_since_mark @ 0x24d2c  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int thunk_FUN_00074f68(void);
int get_elapsed_ms_since_mark(void)
{
  int iVar1;
  iVar1 = thunk_FUN_00074f68();
  return iVar1 - *(volatile int32_t*)((uintptr_t)&g_elapsed_time_mark) /*=0x20007a28*/;
}

