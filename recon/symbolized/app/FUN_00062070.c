#include "g1_app_symbols.h"
/* named: FUN_00062070 */
/* Reconstructed FUN_00062070 @ 0x62070  (parity: 300/300 trials, PROVEN) */

unsigned int FUN_00062070(int param_1, int param_2, unsigned short *param_3)
{
  unsigned int uVar1 = ((uintptr_t)&rodata_186a0) /*=0x186a0*/;
  unsigned int uVar3;

  if ((param_2 <= " size" /*=0xf423f*/) || (param_1 > 0x325aa0)) {
    return 0xffffffea;
  }
  if (param_1 <= " size" /*=0xf423f*/) {
    *param_3 = 0;
    return 0xffffffde;
  }
  if (param_2 <= 0x325aa0) {
    uVar3 = ((unsigned int)param_1 - ((uintptr_t)&rodata_dbba1) /*=0xdbba1*/) / uVar1;
    *param_3 = (unsigned short)uVar3;
    if ((uVar1 * uVar3 + "size" /*=0xf4240*/) <= (unsigned int)param_2) {
      return 0;
    }
    return 0xffffffea;
  }
  *param_3 = 0x17;
  return 0xffffffde;
}

