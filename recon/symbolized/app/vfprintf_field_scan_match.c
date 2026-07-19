#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00079278 @ 0x00079278
 * public-name: vfprintf_field_scan_match
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   vfprintf_field_scan_match                <= FUN_00079278 @ 0x00079278
 * address symbols (name @ address):
 *   rodata_f8a6b                             @ 0x000f8a6b
 */
/* Reconstructed FUN_00079278 @ 0x79278  (parity: 200/200 trials, PROVEN) */

#include <stdint.h>
typedef int (*codep)(int,int*,unsigned,void*,unsigned**);
unsigned vfprintf_field_scan_match(int param_1,unsigned *param_2,int *param_3,unsigned **param_4){
  int iVar1; unsigned uVar2; unsigned *puVar3; int iVar4; unsigned char *unaff_r6; unsigned char *puVar5; int iVar6;
  if (param_2[2] == 0) {
    if (param_2[6] == 0) { uVar2 = 1; } else { uVar2 = 0xffffffff; }
    param_2[2] = uVar2;
  }
  iVar1 = ((unsigned long)&rodata_f8a6b) /*=0xf8a6b*/;
  iVar6 = 0;
  if (-1 < (int)(*param_2 << 0x1b)) {
    puVar3 = (unsigned *)*param_4;
    *param_4 = puVar3 + 1;
    unaff_r6 = (unsigned char *)*puVar3;
  }
  do {
    uVar2 = param_2[6];
    if (uVar2 != 0) {
      if (uVar2 == 1) {
        if (*(char *)(param_2[5] + (unsigned)*(unsigned char *)*param_3) == 0) {
          if (iVar6 == 0) { return 1; }
LAB_00079306:
          if (((*param_2 & 0x10) == 0) && (param_2[3] = param_2[3] + 1, param_2[6] != 0)) {
            *unaff_r6 = 0;
          }
          param_2[4] = param_2[4] + iVar6;
          return 0;
        }
      } else if ((uVar2 != 2) || ((int)((unsigned)*(unsigned char *)(iVar1 + (unsigned)*(unsigned char *)*param_3) << 0x1c) < 0)) goto LAB_00079306;
    }
    iVar6 = iVar6 + 1;
    puVar5 = unaff_r6;
    if (-1 < (int)(*param_2 << 0x1b)) {
      puVar5 = unaff_r6 + 1;
      *unaff_r6 = *(unsigned char *)*param_3;
    }
    iVar4 = param_3[1];
    *param_3 = *param_3 + 1;
    uVar2 = param_2[2];
    param_3[1] = iVar4 + -1;
    uVar2 = uVar2 - 1;
    param_2[2] = uVar2;
    unaff_r6 = puVar5;
    if ((uVar2 == 0) ||
       ((iVar4 + -1 < 1 &&
        (iVar4 = ((codep)param_2[0x60])(param_1,param_3,uVar2,(void*)param_2[0x60],param_4),
        iVar4 != 0)))) goto LAB_00079306;
  } while(1);
}
