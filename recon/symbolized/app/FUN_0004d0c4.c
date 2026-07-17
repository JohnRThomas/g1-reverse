#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0004d0c4 @ 0x0004d0c4
 * public-name: FUN_0004d0c4
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   rpmsg_create_ept                         <= FUN_00070fb4 @ 0x00070fb4
 * address symbols (name @ address):
 *   rodata_7ed27                             @ 0x0007ed27
 */
/* Reconstructed FUN_0004d0c4 @ 0x4d0c4  (parity: 300/300 trials, PROVEN) */

extern int rpmsg_create_ept(int, int, int, int, int, unsigned int, unsigned int, unsigned int);

int FUN_0004d0c4(int *param_1, int param_2, int param_3, unsigned int param_4)
{
  int uVar1;
  if (param_1 == 0 || param_3 == 0) {
    uVar1 = 0xffffffea;
  } else if (param_2 == 1) {
    uVar1 = rpmsg_create_ept(param_3, (int)param_1 + 0xe0, param_3 + 0x40, -1, -1,
                         *(unsigned int *)((char *)param_1 + 0x1ac), ((unsigned long)&rodata_7ed27) /*=0x7ed27*/, param_4);
  } else {
    uVar1 = 0;
  }
  return uVar1;
}
