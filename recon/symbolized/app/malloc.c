#include "g1_app_symbols.h"
/* named: malloc */
/* globals referenced:
//   0x20002d20  g_libc_heap_ctrl             
*/
/* Reconstructed malloc @ 0x76d6c  (parity: 300/300 trials, PROVEN) */

extern void _malloc_r(unsigned int a0, unsigned int a1);
void malloc(unsigned int param_1)
{
  _malloc_r(*(volatile unsigned int*)((uintptr_t)&g_libc_heap_ctrl) /*=0x20002d20*/, param_1);
}

