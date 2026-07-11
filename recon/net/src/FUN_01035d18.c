/* net-core FUN_01035d18 @ 0x1035d18  (parity 300 trials PROVEN) */
#include <stdint.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"
static inline int isCurrentModePrivileged(void){return (__get_CONTROL()&1)==0;}
static inline int getBasePriority(void){return (int)__get_BASEPRI();}
static inline void setBasePriority(int p){__set_BASEPRI((unsigned)p);}
static inline void InstructionSynchronizationBarrier(int x){(void)x;__ISB();}
static inline unsigned int getCurrentExceptionNumber(void){return __get_IPSR();}

extern unsigned long long FUN_0102c4e4(int, unsigned int, unsigned int);
extern int FUN_0103610c(int);
extern int FUN_01036128(int);
extern void FUN_01036144(int);
extern void FUN_010375b8(int, unsigned int, int, int, int, int);
extern void FUN_01039bb0(unsigned int, unsigned int);
extern void FUN_01039bbe(unsigned int, unsigned int, unsigned int);
extern void FUN_0103b304(int*);
extern void FUN_0103b34c(int*, int, int, int);

#define DAT_01035e10 0x0103d3b6u
#define DAT_01035e14 0x0103d2a7u
#define DAT_01035e18 0x0103e9feu

int FUN_01035d18(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4,
                  int param_5, int param_6)
{
  int bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  unsigned int uVar5;
  unsigned int uVar6;
  unsigned int uVar7;
  int iVar8;
  unsigned long long uVar9;
  int local_30;
  int iStack_2c;

  iVar8 = param_1 + 0x14;
  FUN_0103b304(&local_30);
  iVar2 = iStack_2c;
  iVar4 = local_30;
  uVar7 = 0;
  bVar1 = isCurrentModePrivileged();
  if (bVar1) {
    uVar7 = getBasePriority();
  }
  bVar1 = isCurrentModePrivileged();
  if (bVar1) {
    uVar6 = getBasePriority();
    if (uVar6 == 0 || 0x40 < uVar6) {
      setBasePriority(0x40);
    }
  }
  InstructionSynchronizationBarrier(0xf);
  iVar3 = FUN_0103610c(iVar8);
  uVar9 = 0;
  if (iVar3 == 0) {
LAB_01035d56:
    FUN_01039bbe(DAT_01035e14, DAT_01035e10, 0x72);
    uVar5 = 0x72;
    uVar7 = DAT_01035e10;
  } else {
    FUN_01036144(iVar8);
    uVar6 = 0;
    bVar1 = isCurrentModePrivileged();
    if (bVar1) {
      uVar6 = getCurrentExceptionNumber();
      uVar6 = uVar6 & 0x1f;
    }
    if ((uVar6 == 0) || (param_5 == 0 && param_6 == 0)) {
      while (1) {
        uVar9 = FUN_0102c4e4(param_1, param_2, param_3);
        if (((int)uVar9 != 0) || (param_5 == 0 && param_6 == 0)) break;
        FUN_0103b34c(&local_30, (int)(uVar9 >> 0x20), iVar4, iVar2);
        param_6 = iStack_2c;
        param_5 = local_30;
        FUN_010375b8(iVar8, uVar7, param_1 + 0xc, iStack_2c, local_30, iStack_2c);
        uVar7 = 0;
        bVar1 = isCurrentModePrivileged();
        if (bVar1) {
          uVar7 = getBasePriority();
        }
        bVar1 = isCurrentModePrivileged();
        if (bVar1) {
          uVar6 = getBasePriority();
          if (uVar6 == 0 || 0x40 < uVar6) {
            setBasePriority(0x40);
          }
        }
        InstructionSynchronizationBarrier(0xf);
        iVar3 = FUN_0103610c(iVar8);
        if (iVar3 == 0) goto LAB_01035d56;
        FUN_01036144(iVar8);
      }
      iVar4 = FUN_01036128(iVar8);
      if (iVar4 != 0) {
        bVar1 = isCurrentModePrivileged();
        if (bVar1) {
          setBasePriority((int)uVar7);
        }
        InstructionSynchronizationBarrier(0xf);
        return (int)uVar9;
      }
      FUN_01039bbe(DAT_01035e14, DAT_01035e10, 0xf0);
      uVar5 = 0xf0;
      uVar7 = DAT_01035e10;
    } else {
      FUN_01039bbe(DAT_01035e14, DAT_01035e18, 0x4a);
      uVar5 = 0x4a;
      uVar7 = DAT_01035e18;
    }
  }
  FUN_01039bb0(uVar7, uVar5);
  __builtin_unreachable();
}
