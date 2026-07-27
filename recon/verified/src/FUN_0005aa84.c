/* Reconstructed FUN_0005aa84 @ 0x5aa84  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_0007e2ec(int,...);
extern void FUN_0007e2fa(unsigned long, ...);
extern int FUN_00082712(int,...);
void FUN_0005aa84(unsigned int param_1, int param_2, int param_3, int param_4, short param_5, int param_6, int param_7)
{
  short local_2a[3];
  if (param_5 == 0) param_5 = -1;
  if (param_1 <= *(volatile unsigned short*)0x2000ff3cUL) {
    int *piVar4 = (int*)0x88058;
    unsigned int uVar6 = 1;
    unsigned int uVar2 = 0;
    while (1) {
      if ((int*)0x88070 < piVar4) {
        FUN_0007e2fa(0x99cbd,0xf49a5,0xf46b8,0x7d7);
        FUN_0007e2fa(0xf0d20);
        FUN_0007e2ec(0xf46b8,0x7d7);
      }
      if ((int*)0x88070 <= piVar4) break;
      if ((unsigned int)(*(volatile int*)((int)piVar4+4) + uVar6) < param_1) {
        uVar2 = (*(volatile int*)((int)piVar4+4) + uVar6) & 0xffff;
      } else {
        unsigned int uVar5;
        for (uVar5 = 0; (uVar2 = (uVar6+uVar5)&0xffff), uVar5 < (unsigned int)*(volatile int*)((int)piVar4+4); uVar5++) {
          int iVar1 = FUN_00082712(uVar5*0x14 + *(volatile int*)piVar4, uVar2, param_1, param_2, param_3, param_4, &param_5, param_6, param_7);
          if (iVar1 == 0) return;
        }
      }
      piVar4 += 2;
      uVar6 = uVar2;
    }
  }
  local_2a[0] = param_5;
  unsigned int *puVar3 = (unsigned int*)*(volatile int*)0x2000af08UL;
  if (puVar3 != 0) {
    do {
      unsigned int uVar6 = *puVar3;
      if (uVar6 == 0) {
        LAB_ab44:
        for (; uVar6 < puVar3[-1]; uVar6++) {
          int iVar1 = uVar6*0x14 + puVar3[-2];
          iVar1 = FUN_00082712(iVar1, *(unsigned short*)(iVar1+0x10), param_1, param_2, param_3, param_4, local_2a, param_6, param_7);
          if (iVar1 == 0) return;
        }
      } else if (param_1 < *(unsigned short*)(*(int*)(uVar6-8)+0x10)) {
        uVar6 = 0; goto LAB_ab44;
      }
      puVar3 = (unsigned int*)*puVar3;
    } while (puVar3 != 0);
  }
}

