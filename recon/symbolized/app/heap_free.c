#include "g1_app_symbols.h"
/* named: heap_free */
/* globals referenced:
//   0x20002d20  g_libc_heap_ctrl             
*/
/* Reconstructed heap_free @ 0x76d7c  (parity: 300/300 trials, PROVEN) */

extern void heap_free_core(unsigned int a0, unsigned int a1);
void heap_free(unsigned int param_1)
{
  heap_free_core(*(volatile unsigned int*)((uintptr_t)&g_libc_heap_ctrl) /*=0x20002d20*/, param_1);
}

