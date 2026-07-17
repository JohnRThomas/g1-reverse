#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007f150 @ 0x0007f150
 * public-name: FUN_0007f150
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   flash_area_open                          <= FUN_0004e048 @ 0x0004e048
 *   stream_flash_init                        <= FUN_0004e2b4 @ 0x0004e2b4
 */
/* Reconstructed FUN_0007f150 @ 0x7f150  (parity: 300/300 trials, PROVEN) */

extern int flash_area_open(unsigned int, void*);
extern unsigned int FUN_0007f00e(unsigned int);
extern int stream_flash_init(void*, unsigned int, void*, unsigned int, unsigned int, unsigned int, unsigned int);

int FUN_0007f150(char *param_1, unsigned int param_2)
{
  int iVar1 = flash_area_open(param_2, (void*)(param_1+0x200));
  if (iVar1==0) {
    unsigned int uVar2 = FUN_0007f00e(*(unsigned int*)(param_1+0x200));
    iVar1 = stream_flash_init(param_1+0x204, uVar2, param_1, 0x200,
                         *(unsigned int*)(*(unsigned int*)(param_1+0x200)+4),
                         *(unsigned int*)(*(unsigned int*)(param_1+0x200)+8), 0);
  }
  return iVar1;
}
