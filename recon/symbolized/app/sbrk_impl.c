#include "g1_app_symbols.h"
/* named: sbrk_impl */
/* globals referenced:
//   0x2000a808  g_heap_brk                   
//   0x2005314c  g_heap_base                  
*/
/* Reconstructed sbrk_impl @ 0x51074  (parity: 300/300 trials, PROVEN) */

int sbrk_impl(int param_1)
{
  int iVar1;
  unsigned int uVar2;
  unsigned int uVar3;
  iVar1 = ((uintptr_t)&g_heap_base) /*=0x2005314c*/;
  uVar3 = *(volatile unsigned int*)((uintptr_t)&g_heap_brk) /*=0x2000a808*/;
  uVar2 = (unsigned int)param_1 + uVar3;
  if (uVar2 < (unsigned int)(((uintptr_t)&g_heap_end) /*=0x20070000*/ - ((uintptr_t)&g_heap_base) /*=0x2005314c*/)) {
    *(volatile unsigned int*)((uintptr_t)&g_heap_brk) /*=0x2000a808*/ = uVar2;
    iVar1 = iVar1 + uVar3;
  } else {
    iVar1 = -1;
  }
  return iVar1;
}

