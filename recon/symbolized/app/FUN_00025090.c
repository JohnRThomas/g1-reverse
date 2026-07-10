#include "g1_app_symbols.h"
/* named: FUN_00025090 */
/* Reconstructed FUN_00025090 @ 0x25090  (parity: 300/300 trials, PROVEN) */

unsigned int FUN_00025090(unsigned char *param_1, unsigned int *param_2)
{
  unsigned int uVar1 = 7;
  if (param_1 != 0 && param_2 != 0) {
    *param_1 = 7;
    uVar1 = 0;
    *(unsigned int *)(param_1 + 4) = ((uintptr_t)&tbl_7c38b) /*=0x7c38b*/;
    *(unsigned int *)(param_1 + 8) = ((uintptr_t)&tbl_24a20) /*=0x24a41*/;
    *(unsigned int *)(param_1 + 0xc) = ((uintptr_t)&tbl_24fe0) /*=0x25021*/;
    *(unsigned int *)(param_1 + 0x10) = *param_2;
    *(unsigned int *)(param_1 + 0x14) = param_2[1];
    *(unsigned short *)(param_1 + 0x18) = *(unsigned short *)(param_2 + 2);
  }
  return uVar1;
}

