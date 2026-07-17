#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007da70 @ 0x0007da70
 * public-name: FUN_0007da70
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 */
/* Reconstructed FUN_0007da70 @ 0x7da70  (parity: 300/300 trials, PROVEN) */

extern int memset_bytes(int, unsigned int, unsigned int, int, unsigned int);

int FUN_0007da70(unsigned char *param_1, unsigned int param_2, int param_3, unsigned int param_4)
{
  unsigned char bVar1;
  unsigned char *pbVar2;
  int iVar3;
  iVar3 = 0;
  pbVar2 = param_1;
  while (1) {
    if (param_2 <= (unsigned int)(pbVar2 - param_1)) break;
    bVar1 = *pbVar2;
    memset_bytes(param_3 + iVar3, pbVar2[1], (unsigned int)bVar1, (int)(pbVar2 - param_1), param_4);
    iVar3 = iVar3 + (unsigned int)bVar1;
    pbVar2 = pbVar2 + 2;
  }
  return iVar3;
}
