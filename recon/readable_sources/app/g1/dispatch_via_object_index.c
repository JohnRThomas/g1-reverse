#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00060564 @ 0x00060564
 * public-name: dispatch_via_object_index
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   clock_control_nrf_on                     <= FUN_000604e4 @ 0x000604e4
 *   dispatch_via_object_index                <= FUN_00060564 @ 0x00060564
 * address symbols (name @ address):
 *   rodata_87b30                             @ 0x00087b30
 */
/* Reconstructed FUN_00060564 @ 0x60564  (parity: 300/300 trials, PROVEN) */

extern unsigned int clock_control_nrf_on(unsigned int,int,unsigned int);
typedef void (*fnptr)(int,unsigned int);
void dispatch_via_object_index(int param_1, fnptr UNRECOVERED_JUMPTABLE)
{
  unsigned int uVar1;
  uVar1 = clock_control_nrf_on(((unsigned long)&rodata_87b30) /*=0x87b30*/,(param_1 - 0x2000b098) >> 5,0x40);
  (*UNRECOVERED_JUMPTABLE)(param_1,uVar1);
  return;
}
