#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00086b40 @ 0x00086b40
 * public-name: FUN_00086b40
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Full ABI-faithful reconstruction FUN_00086b40 @ 0x86b40 (62-byte extent; CFG PASS). */

typedef unsigned int (*fp_t)(int,int,unsigned int,int,unsigned int);
unsigned int FUN_00086b40(int param_1, fp_t param_2, unsigned int param_3, unsigned int param_4)
{
  int *piVar3 = (int*)(param_1+0x48);
  unsigned int uVar5=0;
  do {
    int iVar6 = piVar3[1];
    int iVar4 = piVar3[2];
    while (--iVar6 >= 0) {
      if (*(volatile unsigned short*)(iVar4+0xc) > 1) {
        int iVar2 = *(volatile short*)(iVar4+0xe) + 1;
        if (iVar2 != 0) {
          unsigned int uVar1 = param_2(param_1, iVar4, param_3, iVar2, param_4);
          uVar5 |= uVar1;
        }
      }
      iVar4 += 0x68;
    }
    piVar3 = (int*)*piVar3;
  } while (piVar3 != 0);
  return uVar5;
}
