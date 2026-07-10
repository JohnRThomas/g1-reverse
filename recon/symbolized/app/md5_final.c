#include "g1_app_symbols.h"
/* named: md5_final */
/* globals referenced:
//   0x200034f7  g_md5_padding                
*/
/* Reconstructed md5_final @ 0x4a16c  (parity: 300/300 trials, PROVEN) */

extern void u32_to_bytes_le_array(void *dst, void *src, int n);
extern void md5_update_block(void *dst, void *src, int n);

void md5_final(int *param_1, void *param_2)
{
  unsigned int uVar1;
  int iVar2;
  unsigned char localBuf[8];

  uVar1 = ((unsigned int)*param_1 >> 3) & 0x3f;
  if (uVar1 < 0x38) {
    iVar2 = 0x38 - uVar1;
  } else {
    iVar2 = 0x78 - uVar1;
  }
  u32_to_bytes_le_array(localBuf, param_1, 8);
  md5_update_block(param_1, (void*)((uintptr_t)&g_md5_padding) /*=0x200034f7*/, iVar2);
  md5_update_block(param_1, localBuf, 8);
  u32_to_bytes_le_array(param_2, (char*)param_1+8, 0x10);
  return;
}

