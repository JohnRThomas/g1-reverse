#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00064c3c @ 0x00064c3c
 * public-name: cjson_create_bool
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   cjson_create_bool                        <= FUN_00064c3c @ 0x00064c3c
 *   alloc_zeroed_node                        <= FUN_00084fd4 @ 0x00084fd4
 * address symbols (name @ address):
 *   g_cjson_hooks                            @ 0x20002bac
 */
/* Reconstructed FUN_00064c3c @ 0x64c3c  (parity: 300/300 trials, PROVEN) */

extern int alloc_zeroed_node(unsigned int);
void cjson_create_bool(int param_1)
{
  int iVar1;
  unsigned int uVar2;
  iVar1 = alloc_zeroed_node(*(volatile unsigned int *)((unsigned long)&g_cjson_hooks) /*=0x20002bac*/);
  if (iVar1 != 0) {
    if (param_1 == 0) {
      uVar2 = 1;
    } else {
      uVar2 = 2;
    }
    *(volatile unsigned int *)(iVar1 + 0xc) = uVar2;
  }
}
