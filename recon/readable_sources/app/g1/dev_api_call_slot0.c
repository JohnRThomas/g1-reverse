#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007ca54 @ 0x0007ca54
 * public-name: dev_api_call_slot0
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   dev_api_call_slot0                       <= FUN_0007ca54 @ 0x0007ca54
 */
/* Reconstructed FUN_0007ca54 @ 0x7ca54  (parity: 300/300 trials, PROVEN) */

typedef unsigned int (*fnptr)(int, unsigned int, unsigned int, unsigned int);

unsigned int dev_api_call_slot0(int param_1, unsigned int param_2, unsigned int param_3)
{
  unsigned int uVar1;
  volatile unsigned int * volatile vtab = *(volatile unsigned int * volatile *)(param_1 + 8);
  fnptr f = (fnptr)vtab[0];

  if (f != (fnptr)0) {
    uVar1 = f(param_1,param_2,0,param_3);
    return uVar1;
  }
  return 0xffffffa8;
}
