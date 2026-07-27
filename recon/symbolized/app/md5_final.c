#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0004a16c @ 0x0004a16c
 * public-name: md5_final
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   md5_final                                <= FUN_0004a16c @ 0x0004a16c
 *   u32_to_bytes_le_array                    <= FUN_0007d894 @ 0x0007d894
 *   md5_update                               <= FUN_0007d8f4 @ 0x0007d8f4
 * address symbols (name @ address):
 *   g_md5_padding                            @ 0x200034f7
 */
/* Reconstructed FUN_0004a16c @ 0x4a16c  (parity: 300/300 trials, PROVEN) */

extern void u32_to_bytes_le_array(void *dst, void *src, int n);
extern void md5_update(unsigned long*, const unsigned char*, unsigned long);

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
  md5_update(param_1, (void*)((unsigned long)&g_md5_padding) /*=0x200034f7*/, iVar2);
  md5_update(param_1, localBuf, 8);
  u32_to_bytes_le_array(param_2, (char*)param_1+8, 0x10);
  return;
}
