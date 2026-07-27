#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000876ec @ 0x000876ec
 * public-name: _realloc_r
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   _free_r                                  <= FUN_00076d8c @ 0x00076d8c
 *   _malloc_r                                <= FUN_00076e20 @ 0x00076e20
 *   memcpy                                   <= FUN_00086c04 @ 0x00086c04
 *   _realloc_r                               <= FUN_000876ec @ 0x000876ec
 *   _malloc_usable_size_r                    <= FUN_00087996 @ 0x00087996
 */
/* Reconstructed FUN_000876ec @ 0x876ec  (parity: 300/300 trials, PROVEN) */

extern void _free_r(unsigned int a, int b);
extern int _malloc_r(unsigned int a, unsigned int b, unsigned int c, unsigned int d);
extern void memcpy(int, int, int);
extern unsigned int _malloc_usable_size_r(void);
int _realloc_r(unsigned int param_1,int param_2,unsigned int param_3,unsigned int param_4)
{
  int iVar1;
  unsigned int uVar2;

  if (param_2 == 0) {
    iVar1 = _malloc_r(param_1,param_3,param_3,param_4);
    return iVar1;
  }
  if (param_3 == 0) {
    _free_r(param_1, param_2);
  } else {
    uVar2 = _malloc_usable_size_r();
    if (param_3 <= uVar2) {
      return param_2;
    }
    iVar1 = _malloc_r(param_1,param_3,param_3,param_4);
    if (iVar1 != 0) {
      memcpy(iVar1,param_2,param_3);
      _free_r(param_1,param_2);
      return iVar1;
    }
  }
  return 0;
}
