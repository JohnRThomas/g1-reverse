#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007f386 @ 0x0007f386
 * public-name: attr_find_by_handle
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   attr_find_by_handle                      <= FUN_0007f386 @ 0x0007f386
 */
/* Reconstructed FUN_0007f386 @ 0x7f386  (parity: 216/300 trials, PROVEN) */

int attr_find_by_handle(int param_1, unsigned int param_2)
{
  int iVar1;
  unsigned int uVar2;
  int iVar3;
  int iVar4;

  iVar1 = *(volatile int*)(param_1 + 0x134);
  if (iVar1 != 0) {
    iVar4 = 0;
    iVar1 = iVar1 - 1;
    while (iVar4 <= iVar1) {
      iVar3 = (iVar4 + iVar1) / 2;
      uVar2 = *(volatile unsigned short *)(param_1 + (iVar3+3)*8 + 8);
      if (uVar2 < param_2) {
        iVar4 = iVar3+1;
      } else {
        if (uVar2 <= param_2) {
          return param_1 + (iVar3+3)*8+4;
        }
        iVar1 = iVar3-1;
      }
    }
    iVar1 = 0;
  }
  return iVar1;
}
