/* Reconstructed FUN_00074060 @ 0x74060  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"
extern int FUN_00072040(unsigned);
extern int FUN_0007205c(unsigned);
extern void FUN_00072078(unsigned);
extern void FUN_000737d8(int);
extern void FUN_00073cdc(void*,int*,int,int,unsigned);
extern void FUN_0007e2ec(unsigned,unsigned);
extern void FUN_0007e2fa(unsigned,unsigned,unsigned,unsigned);
int FUN_00074060(int *param_1, char param_2, unsigned param_3, unsigned param_4)
{
  unsigned basepri, uVar10, uVar5; int iVar3, iVar4;
  unsigned *puVar6, *puVar8, *puVar9; unsigned char bVar7;
  uVar10 = 0; uVar5 = 0;
  basepri = __get_BASEPRI();
  __set_BASEPRI_MAX(0x20u);
  __ISB();
  uVar10 = basepri;
  iVar3 = FUN_00072040(0x2000b490);
  if (iVar3 == 0) {
    FUN_0007e2fa(0x00099cbd, 0x000f0920, 0x000f08c7, 0x72);
    FUN_0007e2fa(0x000f0935, 0x2000b490, 0, 0);
    uVar5 = 0x72; uVar10 = 0x000f08c7;
  } else {
    FUN_00072078(0x2000b490);
    puVar8 = (unsigned*)0x2000b464;
    if (((*(unsigned char*)((int)param_1 + 0xd) & 0x1f) == 0) && (param_1[6] == 0)) {
      bVar7 = *(unsigned char*)((int)param_1 + 0xd) & 0x7f;
      *(volatile unsigned char*)((int)param_1 + 0xd) = bVar7;
      FUN_00073cdc(puVar8, param_1, 0, bVar7, param_4);
      *(volatile char*)((int)param_1 + 0xe) = param_2;
      *(volatile unsigned char*)((int)param_1 + 0xd) = *(unsigned char*)((int)param_1 + 0xd) | 0x80;
      if (param_1 == (int*)0x20006720) {
        FUN_0007e2fa(0x00099cbd, 0x000f84d6, 0x000f82f4, 0xc1);
        uVar5 = 0xc1; uVar10 = 0x000f82f4;
        goto LABe0;
      }
      puVar9 = (unsigned*)0;
      if ((unsigned*)*puVar8 != puVar8) puVar9 = (unsigned*)*puVar8;
      puVar6 = (unsigned*)puVar8[1];
      for (; puVar9 != 0; puVar9 = (unsigned*)*puVar9) {
        if ((param_2 != *(char*)((int)puVar9 + 0xe)) && (param_2 < *(char*)((int)puVar9 + 0xe))) {
          puVar8 = (unsigned*)puVar9[1];
          *(volatile unsigned*)param_1 = (unsigned)puVar9;
          *(volatile unsigned*)(param_1+1) = (unsigned)puVar8;
          *(volatile unsigned*)puVar8 = (unsigned)param_1;
          *(volatile unsigned*)(puVar9+1) = (unsigned)param_1;
          goto LAB138;
        }
        if (puVar6 == puVar9) break;
      }
      *(volatile unsigned*)param_1 = (unsigned)puVar8;
      *(volatile unsigned*)(param_1+1) = (unsigned)puVar6;
      *(volatile unsigned*)puVar6 = (unsigned)param_1;
      *(volatile unsigned*)(puVar8+1) = (unsigned)param_1;
LAB138:
      FUN_000737d8(1);
    } else {
      iVar3 = 0;
      *(volatile char*)((int)param_1 + 0xe) = param_2;
    }
    iVar4 = FUN_0007205c(0x2000b490);
    if (iVar4 != 0) {
      __set_BASEPRI(uVar10);
      __ISB();
      return iVar3;
    }
    FUN_0007e2fa(0x00099cbd, 0x000f08f4, 0x000f08c7, 0xf0);
    FUN_0007e2fa(0x000f090b, 0x2000b490, 0, 0);
    uVar5 = 0xf0; uVar10 = 0x000f08c7;
  }
LABe0:
  FUN_0007e2ec(uVar10, uVar5);
  return 0;
}
