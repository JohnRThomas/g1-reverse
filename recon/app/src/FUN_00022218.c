/* Reconstructed FUN_00022218 @ 0x22218  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t undefined4; typedef unsigned int uint; typedef unsigned char byte;
extern int DEBUG_PRINT(int,...); extern int FUN_0000eefe(int,...); extern int FUN_000167a8(int,...);
extern int FUN_00019c70(int,...); extern int FUN_00034bcc(int,...);
typedef int (*codeptr)(int,...);

int FUN_00022218(undefined4 param_1,undefined4 param_2,codeptr param_3,undefined4 param_4)
{
  int iVar1; undefined4 uVar2; undefined4 uVar3; uint *puVar4; uint uVar5; int iVar6;
  iVar1 = FUN_0000eefe(param_1,0x9e1a8);
  if (iVar1 == 0) {
    uVar2 = FUN_00034bcc(0); uVar3 = 0x15e2;
LAB_2232:
    iVar1 = (*param_3)(param_4,uVar2,uVar3);
    if (-1 < iVar1) return 0;
    iVar6 = *(volatile int*)0x2000230c;
LAB_2270:
    if (iVar6 < 2) return iVar1;
    if (*(volatile int*)0x20007554 == 0) { DEBUG_PRINT(0x9e1ba,0x9e53c,param_1,iVar1); return iVar1; }
    FUN_00019c70(0x9e1ba,0x9e53c,param_1,iVar1);
    return iVar1;
  }
  iVar1 = FUN_0000eefe(param_1,0x9e1de);
  if (iVar1 == 0) {
    iVar1 = FUN_000167a8(0);
    if (*(int *)(iVar1 + 0xfec) == 0) return 0;
    iVar1 = FUN_000167a8(0);
    iVar1 = (*param_3)(param_4,*(undefined4 *)(iVar1 + 0xfec),0x6a);
    iVar6 = *(volatile int*)0x2000230c;
    if (iVar1 < 0) goto LAB_2270;
    if (iVar6 < 3) return 0;
    if (*(volatile int*)0x20007554 == 0) {
      iVar1 = FUN_000167a8(0); puVar4 = *(uint **)(iVar1 + 0xfec);
LAB_22b4: uVar5 = *puVar4;
LAB_22b6: DEBUG_PRINT(0x9e1eb,0x9e53c,param_1,uVar5); return 0;
    }
    iVar1 = FUN_000167a8(0); puVar4 = *(uint **)(iVar1 + 0xfec);
  } else {
    iVar1 = FUN_0000eefe(param_1,0x9e201);
    if (iVar1 != 0) {
      iVar1 = FUN_0000eefe(param_1,0x9e20e);
      if (iVar1 == 0) {
        iVar1 = FUN_000167a8(0);
        iVar1 = (*param_3)(param_4,iVar1 + 0x1050,4);
        iVar6 = *(volatile int*)0x2000230c;
        if (iVar1 < 0) goto LAB_2270;
        if (iVar6 < 3) return 0;
        if (*(volatile int*)0x20007554 != 0) { iVar1 = FUN_000167a8(0); uVar5 = *(uint *)(iVar1 + 0x1050); goto LAB_22a0; }
        iVar1 = FUN_000167a8(0); uVar5 = *(uint *)(iVar1 + 0x1050); goto LAB_22b6;
      }
      iVar1 = FUN_0000eefe(param_1,0x9e21f);
      if (iVar1 == 0) {
        iVar1 = FUN_000167a8(0);
        iVar1 = (*param_3)(param_4,iVar1 + 0xed5,1);
        iVar6 = *(volatile int*)0x2000230c;
        if (iVar1 < 0) goto LAB_2270;
        if (iVar6 < 3) return 0;
        if (*(volatile int*)0x20007554 == 0) { iVar1 = FUN_000167a8(0); uVar5 = (uint)*(byte *)(iVar1 + 0xed5); goto LAB_22b6; }
        iVar1 = FUN_000167a8(0); uVar5 = (uint)*(byte *)(iVar1 + 0xed5); goto LAB_22a0;
      }
      iVar1 = FUN_0000eefe(param_1,0x9e230);
      if (iVar1 == 0) {
        iVar1 = FUN_000167a8(0);
        iVar1 = (*param_3)(param_4,iVar1 + 0xf60,1);
        iVar6 = *(volatile int*)0x2000230c;
        if (iVar1 < 0) goto LAB_2270;
        if (iVar6 < 3) return 0;
        if (*(volatile int*)0x20007554 == 0) { iVar1 = FUN_000167a8(0); uVar5 = (uint)*(byte *)(iVar1 + 0xf60); goto LAB_22b6; }
        iVar1 = FUN_000167a8(0); uVar5 = (uint)*(byte *)(iVar1 + 0xf60); goto LAB_22a0;
      }
      iVar1 = FUN_0000eefe(param_1,0x9e23c);
      if (iVar1 == 0) {
        iVar1 = FUN_000167a8(0);
        iVar1 = (*param_3)(param_4,iVar1 + 0xfea,1);
        iVar6 = *(volatile int*)0x2000230c;
        if (iVar1 < 0) goto LAB_2270;
        if (iVar6 < 3) return 0;
        if (*(volatile int*)0x20007554 == 0) { iVar1 = FUN_000167a8(0); uVar5 = (uint)*(byte *)(iVar1 + 0xfea); goto LAB_22b6; }
        iVar1 = FUN_000167a8(0); uVar5 = (uint)*(byte *)(iVar1 + 0xfea); goto LAB_22a0;
      }
      iVar1 = FUN_0000eefe(param_1,0x990cf);
      if (iVar1 == 0) {
        iVar1 = FUN_000167a8(0);
        iVar1 = (*param_3)(param_4,iVar1 + 1);
        iVar6 = *(volatile int*)0x2000230c;
        if (iVar1 < 0) goto LAB_2270;
        if (iVar6 < 3) return 0;
        if (*(volatile int*)0x20007554 == 0) { iVar1 = FUN_000167a8(0); uVar5 = (uint)*(byte *)(iVar1 + 1); goto LAB_22b6; }
        iVar1 = FUN_000167a8(0); uVar5 = (uint)*(byte *)(iVar1 + 1); goto LAB_22a0;
      }
      iVar1 = FUN_0000eefe(param_1,0x9e249);
      if (iVar1 != 0) {
        iVar1 = FUN_0000eefe(param_1,0x9e259);
        if (iVar1 != 0) return 0;
        iVar1 = FUN_000167a8(0);
        iVar1 = (*param_3)(param_4,iVar1 + 0xef4,1);
        iVar6 = *(volatile int*)0x2000230c;
        if (iVar1 < 0) goto LAB_2270;
        if (iVar6 < 3) return 0;
        if (*(volatile int*)0x20007554 == 0) { iVar1 = FUN_000167a8(0); uVar5 = (uint)*(byte *)(iVar1 + 0xef4); goto LAB_22b6; }
        iVar1 = FUN_000167a8(0); uVar5 = (uint)*(byte *)(iVar1 + 0xef4); goto LAB_22a0;
      }
      iVar1 = FUN_000167a8(0);
      if (*(int *)(iVar1 + 0xff4) == 0) return 0;
      iVar1 = FUN_000167a8(0);
      uVar3 = 0x16a; uVar2 = *(undefined4 *)(iVar1 + 0xff4);
      goto LAB_2232;
    }
    iVar1 = FUN_000167a8(0);
    if (*(int *)(iVar1 + 0xff0) == 0) return 0;
    iVar1 = FUN_000167a8(0);
    iVar1 = (*param_3)(param_4,*(undefined4 *)(iVar1 + 0xff0),7);
    iVar6 = *(volatile int*)0x2000230c;
    if (iVar1 < 0) goto LAB_2270;
    if (iVar6 < 3) return 0;
    if (*(volatile int*)0x20007554 == 0) { iVar1 = FUN_000167a8(0); puVar4 = *(uint **)(iVar1 + 0xff0); goto LAB_22b4; }
    iVar1 = FUN_000167a8(0); puVar4 = *(uint **)(iVar1 + 0xff0);
  }
  uVar5 = *puVar4;
LAB_22a0:
  FUN_00019c70(0x9e1eb,0x9e53c,param_1,uVar5);
  return 0;
}

