#include "g1_app_symbols.h"
/* named: format_string_to_buffer */
/* globals referenced:
//   0x20002d20  g_libc_heap_ctrl             
*/
/* Reconstructed format_string_to_buffer @ 0x7797c  (parity: 300/300 trials, PROVEN) */

extern void FUN_00078d90(int, void*, int);

void format_string_to_buffer(unsigned char *param_1, int param_2, int param_3, int param_4)
{
  int r0;
  unsigned char *local_78[2];
  r0 = *(volatile int*)((uintptr_t)&g_libc_heap_ctrl) /*=0x20002d20*/;
  local_78[0] = param_1;
  FUN_00078d90(r0, local_78, param_2);
  *(volatile unsigned char *)param_1 = 0;
}

