#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00051074 @ 0x00051074
 * public-name: sbrk_impl
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   sbrk_impl                                <= FUN_00051074 @ 0x00051074
 * address symbols (name @ address):
 *   g_heap_brk                               @ 0x2000a808
 */
/* Reconstructed FUN_00051074 @ 0x51074  (parity: 300/300 trials, PROVEN) */

int sbrk_impl(int param_1)
{
  int iVar1;
  unsigned int uVar2;
  unsigned int uVar3;
  iVar1 = 0x2005314c;
  uVar3 = *(volatile unsigned int*)((unsigned long)&g_heap_brk) /*=0x2000a808*/;
  uVar2 = (unsigned int)param_1 + uVar3;
  if (uVar2 < (unsigned int)(0x20070000UL - 0x2005314cUL)) {
    *(volatile unsigned int*)((unsigned long)&g_heap_brk) /*=0x2000a808*/ = uVar2;
    iVar1 = iVar1 + uVar3;
  } else {
    iVar1 = -1;
  }
  return iVar1;
}
