/* Reconstructed FUN_0004b908 @ 0x4b908  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_0004b4fc(int,...);
extern int FUN_00072040(int,...);
extern int FUN_0007205c(int,...);
extern int FUN_00072078(int,...);
extern int FUN_0007e1c6(int,...);
extern int FUN_0007e1e6(int,...);
extern int FUN_0007e2ec(int,...);
extern int FUN_0007e2fa(int,...);
unsigned int FUN_0004b908(int *param_1, int *param_2)
{
  unsigned int uVar3 = (unsigned int)FUN_0007e1c6(0);
  if ((int)uVar3 < 0) return uVar3;
  int *puVar8 = param_1 + 5;
  int iVar4 = FUN_00072040((int)puVar8);
  if (iVar4 == 0) {
    FUN_0007e2fa(0x99cbd,0xf0920,0xf08c7,0x72);
    FUN_0007e2fa(0xf0935,(int)puVar8);
    FUN_0007e2ec(0xf08c7,0x72);
    return 0;
  }
  FUN_00072078((int)puVar8);
  unsigned short uVar1 = *(unsigned short*)((int)param_1+0x1c);
  uVar3 = uVar1 & 7;
  unsigned int uVar7;
  if (*(short*)((int)param_1+0x1e) == -1) {
    uVar7 = 0xfffffff5;
    iVar4 = 0;
  } else {
    uVar7 = uVar3;
    if (uVar3 != 2) {
      switch (uVar3) {
        case 0: case 4: case 6:
          *param_2 = 0;
          if (param_1[1] == 0) { *param_1 = (int)param_2; param_1[1] = (int)param_2; }
          else { *(int*)param_1[1] = (int)param_2; param_1[1] = (int)param_2; }
          if ((uVar1 & 7) == 0) { FUN_0004b4fc((int)param_1, 2, 0); return uVar3; }
          break;
        case 1: uVar7 = 0xfffffffb; break;
        case 5: uVar7 = 0xffffff7a; break;
        default:
          FUN_0007e2fa(0x99cbd,0xf08b1,0xf0824,0x1c8);
          FUN_0007e2ec(0xf0824,0x1c8);
          return 0;
      }
      iVar4 = 0;
      goto LAB_b9a6;
    }
    *(short*)((int)param_1+0x1e) = *(short*)((int)param_1+0x1e) + 1;
  }
LAB_b9a6:;
  int iVar5 = FUN_0007205c((int)puVar8);
  if (iVar5 != 0) {
    if (iVar4 != 0) FUN_0007e1e6((int)param_1, (int)param_2, uVar3, 0);
    return uVar7;
  }
  FUN_0007e2fa(0x99cbd,0xf08f4,0xf08c7,0xf0);
  FUN_0007e2fa(0xf090b,(int)puVar8);
  FUN_0007e2ec(0xf08c7,0xf0);
  return 0;
}

