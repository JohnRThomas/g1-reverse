/* Reconstructed FUN_00072674 @ 0x72674  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include <cmsis_gcc.h>

static inline int isCurrentModePrivileged(void){return (__get_CONTROL()&1)==0;}
static inline int getBasePriority(void){return (int)__get_BASEPRI();}
static inline void setBasePriority(int p){__set_BASEPRI((uint32_t)p);}
static inline void InstructionSynchronizationBarrier(int x){(void)x;__ISB();}

extern int FUN_00072040(unsigned int*);
extern int FUN_0007205c(unsigned int*);
extern int FUN_00072078(unsigned int*);
extern int FUN_000738d4();
extern int FUN_000739f0(unsigned int*,int);
extern int FUN_000744a4(unsigned int*);
extern unsigned int* FUN_00075944(int,int);
extern int FUN_0007e2ec(int,int);
extern int FUN_0007e2fa(int,...);
extern int FUN_0008688e(unsigned int*,int);

unsigned int FUN_00072674(unsigned int *param_1, unsigned int *param_2, unsigned int *param_3, int param_4, char param_5)
{
  int bVar1;
  int iVar2;
  unsigned int *puVar3;
  unsigned int uVar4;
  unsigned int *puVar5;
  unsigned int uVar6;

  puVar5 = param_1 + 2;
  uVar6 = 0;
  bVar1 = isCurrentModePrivileged();
  if (bVar1) {
    uVar6 = getBasePriority();
  }
  bVar1 = isCurrentModePrivileged();
  if (bVar1 && (uVar4 = getBasePriority(), uVar4 == 0 || 0x20 < uVar4)) {
    setBasePriority(0x20);
  }
  InstructionSynchronizationBarrier(0xf);
  iVar2 = FUN_00072040(puVar5);
  if (iVar2 == 0) {
    FUN_0007e2fa(0x99cbd, 0xf0920, 0xf08c7, 0x72);
    FUN_0007e2fa(0xf0935, puVar5);
    uVar6 = 0x72;
LAB_726b6:
    FUN_0007e2ec(0xf08c7, uVar6);
  }
  FUN_00072078(puVar5);
  if (param_5 != 0) {
    param_2 = (unsigned int*)param_1[1];
  }
  iVar2 = (int)FUN_000744a4(param_1 + 3);
  if (iVar2 != 0) {
    *(unsigned int**)(iVar2 + 0x14) = param_3;
    *(unsigned int*)(iVar2 + 0x90) = 0;
    FUN_000738d4();
    goto LAB_726e2;
  }
  if (param_4 == 0) {
    *param_3 = 0;
  } else {
    puVar3 = FUN_00075944(0, 8);
    if (puVar3 == 0) {
      iVar2 = FUN_0007205c(puVar5);
      if (iVar2 != 0) {
        bVar1 = isCurrentModePrivileged();
        if (bVar1) {
          setBasePriority(uVar6);
        }
        InstructionSynchronizationBarrier(0xf);
        return 0xfffffff4;
      }
      FUN_0007e2fa(0x99cbd, 0xf08f4, 0xf08c7, 0xf0);
      FUN_0007e2fa(0xf090b, puVar5);
      uVar6 = 0xf0;
      goto LAB_726b6;
    }
    puVar3[1] = (unsigned int)(unsigned long)param_3;
    *puVar3 = 1;
    param_3 = puVar3;
  }
  uVar4 = *param_3 & 3;
  if (param_2 == 0) {
    *param_3 = *param_1 | uVar4;
    *param_1 = (unsigned int)(unsigned long)param_3;
    if (param_1[1] == 0) {
LAB_72748:
      param_1[1] = (unsigned int)(unsigned long)param_3;
    }
  } else if (*param_2 < 4) {
    *param_3 = uVar4;
    puVar3 = (unsigned int*)param_1[1];
    if (puVar3 != 0) {
      *puVar3 = (*puVar3 & 3) | (unsigned int)(unsigned long)param_3;
      goto LAB_72748;
    }
    *param_1 = (unsigned int)(unsigned long)param_3;
    param_1[1] = (unsigned int)(unsigned long)param_3;
  } else {
    *param_3 = (*param_2 & 0xfffffffc) | uVar4;
    *param_2 = (unsigned int)(unsigned long)param_3 | (*param_2 & 3);
  }
  FUN_0008688e(param_1 + 5, 4);
LAB_726e2:
  FUN_000739f0(puVar5, uVar6);
  return 0;
}
