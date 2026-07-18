#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000876d0 @ 0x000876d0
 * public-name: _calloc_r
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   _malloc_r                                <= FUN_00076e20 @ 0x00076e20
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 *   _calloc_r                                <= FUN_000876d0 @ 0x000876d0
 */
/* Reconstructed FUN_000876d0 @ 0x876d0  (parity: 300/300 trials, PROVEN) */

extern int _malloc_r(unsigned int, int, int, unsigned int, unsigned int);
extern void memset_bytes(int, int, int);

int _calloc_r(unsigned int param_1,int param_2,int param_3,unsigned int param_4)
{
  int iVar1;

  iVar1 = _malloc_r(param_1,param_3 * param_2,param_3,param_4,param_4);
  if (iVar1 != 0) {
    memset_bytes(iVar1,0,param_3 * param_2);
  }
  return iVar1;
}
