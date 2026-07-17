#include "g1_net_symbols.h"
/* net-core FUN_0102cd8c @ 0x102cd8c  (parity 300 trials PROVEN) */
#include <stdint.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"
static inline int isCurrentModePrivileged(void){return (__get_CONTROL()&1)==0;}
static inline int getBasePriority(void){return (int)__get_BASEPRI();}
static inline void setBasePriority(int p){__set_BASEPRI((unsigned)p);}
static inline void InstructionSynchronizationBarrier(int x){(void)x;__ISB();}

#define P_0102ce0c ((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/
#define P_0102ce10 ((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/

extern int FUN_0103610c(int);
extern int FUN_01036128(int);
extern void FUN_01036144(int);
extern void FUN_01039bb0(int, unsigned int);
extern void FUN_01039bbe(int, int, unsigned int);
extern int FUN_01039c20(int, int, int);
extern void FUN_01039db6(int);

typedef int (*fp0_t)(unsigned char *);

unsigned int FUN_0102cd8c(int param_1, unsigned char *param_2)
{
  int bVar1;
  unsigned int uVar2;
  int uVar3;
  int iVar4;
  int iVar5;
  int uVar6;

  uVar3 = ((fp0_t)(*(int *)(param_1 + 0x1c)))(param_2);
  iVar5 = param_1 + 0x14;
  uVar6 = 0;
  bVar1 = isCurrentModePrivileged();
  if (bVar1) {
    uVar6 = getBasePriority();
  }
  bVar1 = isCurrentModePrivileged();
  if (bVar1) {
    uVar2 = getBasePriority();
    if (uVar2 == 0 || 0x40 < uVar2) {
      setBasePriority(0x40);
    }
  }
  InstructionSynchronizationBarrier(0xf);
  iVar4 = FUN_0103610c(iVar5);
  if (iVar4 == 0) {
    FUN_01039bbe(P_0102ce10, P_0102ce0c, 0x72);
    uVar3 = 0x72;
  } else {
    FUN_01036144(iVar5);
    *param_2 = *param_2 | 1;
    uVar3 = FUN_01039c20(param_1, *(int *)(param_1 + 4), uVar3);
    *(int *)(param_1 + 4) = uVar3;
    FUN_01039db6(param_1);
    iVar5 = FUN_01036128(iVar5);
    if (iVar5 != 0) {
      bVar1 = isCurrentModePrivileged();
      if (bVar1) {
        setBasePriority(uVar6);
      }
      InstructionSynchronizationBarrier(0xf);
      return uVar3;
    }
    FUN_01039bbe(P_0102ce10, P_0102ce0c, 0xf0);
    uVar3 = 0xf0;
  }
  FUN_01039bb0(P_0102ce0c, uVar3);
  return uVar3;
}
