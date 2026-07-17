#include "g1_net_symbols.h"
/* net-core FUN_010384a8 @ 0x10384a8  (parity 36 trials PROVEN) */
typedef unsigned int uint;
#include <stdint.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"
static inline int isCurrentModePrivileged(void){return (__get_CONTROL() & 1u)==0;}
static inline int getBasePriority(void){return (int)__get_BASEPRI();}
static inline void setBasePriority(int p){__set_BASEPRI((unsigned)p);}
static inline void InstructionSynchronizationBarrier(int x){(void)x;__ISB();}

extern int FUN_0103610c(unsigned int);
extern int FUN_01036128(unsigned int);
extern void FUN_01036144(unsigned int);
extern void FUN_01039bb0(unsigned int, unsigned int);
extern void FUN_01039bbe(unsigned int, unsigned int, unsigned int);
extern void FUN_0103b3e0(int, int, char*);

int FUN_010384a8(int param_1,int param_2,char *param_3,int param_4)
{
  unsigned int uVar3 = 0x21004b78u;
  int iVar6 = 0, iVar7 = 0;
  unsigned int uVar8;
  unsigned int uVar5;
  int iVar2;
  unsigned char bVar4;

  for (;;) {
    if (param_2 <= iVar6) return iVar7;
    uVar8 = 0;
    if (isCurrentModePrivileged()) uVar8 = getBasePriority();
    if (isCurrentModePrivileged()) {
      uVar5 = getBasePriority();
      if (uVar5 == 0 || uVar5 > 0x40) setBasePriority(0x40);
    }
    InstructionSynchronizationBarrier(0xf);
    iVar2 = FUN_0103610c(uVar3);
    if (iVar2 == 0) {
      FUN_01039bbe(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/, 0x72u);
      uVar8 = 0x72; uVar3 = ((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/;
      goto LAB_010385aa;
    }
    FUN_01036144(uVar3);
    bVar4 = *(volatile unsigned char *)(param_1 + 0xd) & 0x3f;
    switch (bVar4) {
      case 0: break;
      case 1:
        if (*(volatile int*)(*(volatile int*)(param_1+0x10)+8) == 0) break;
        uVar5 = 1;
        goto LAB_0103851c;
      case 2:
        if (*(volatile int*)(*(volatile int*)(param_1+0x10)+8) != 0) { uVar5 = 2; goto LAB_0103851c; }
        break;
      case 4:
        if (*(volatile int*)(*(volatile int*)(param_1+0x10)) != 0) { uVar5 = 4; goto LAB_0103851c; }
        break;
      case 8:
        if (*(volatile int*)(*(volatile int*)(param_1+0x10)+0x24) != 0) { uVar5 = 0x10; goto LAB_0103851c; }
        break;
      default:
        FUN_01039bbe(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103eb7f) /*=0x103eb7f*/, 99u);
        uVar8 = 99; uVar3 = ((unsigned long)&rodata_103eb7f) /*=0x103eb7f*/;
        goto LAB_010385aa;
    }
    goto SKIP_SET;
  LAB_0103851c:
    *(volatile unsigned int*)(param_1+8) = 0;
    {
      unsigned int c = *(volatile unsigned int*)(param_1+0xc);
      unsigned int nb = uVar5 | ((c << 0xb) >> 0x19);
      *(volatile unsigned int*)(param_1+0xc) = (c & 0xffe03fffu) | (nb << 0xe);
    }
    *param_3 = '\0';
    goto LAB_01038536;
  SKIP_SET:
    if (param_4 == 0 && *param_3 != 0) {
      bVar4 = *(volatile unsigned char *)(param_1 + 0xd) & 0x3f;
      switch (bVar4) {
        case 0:
          goto caseD_0;
        case 1:
          iVar2 = *(volatile int*)(param_1+0x10);
          if (iVar2 == 0) {
            FUN_01039bbe(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103eb7f) /*=0x103eb7f*/, 0x95u);
            uVar8 = 0x95; uVar3 = ((unsigned long)&rodata_103eb7f) /*=0x103eb7f*/;
            goto LAB_010385aa;
          }
          break;
        case 2:
          if (*(volatile int*)(param_1+0x10) == 0) {
            FUN_01039bbe(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103eb7f) /*=0x103eb7f*/, 0x8du);
            uVar8 = 0x8d; uVar3 = ((unsigned long)&rodata_103eb7f) /*=0x103eb7f*/;
            goto LAB_010385aa;
          }
          iVar2 = *(volatile int*)(param_1+0x10) + 0x10;
          break;
        case 4:
          if (*(volatile int*)(param_1+0x10) == 0) {
            FUN_01039bbe(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103eb7f) /*=0x103eb7f*/, 0x91u);
            uVar8 = 0x91; uVar3 = ((unsigned long)&rodata_103eb7f) /*=0x103eb7f*/;
            goto LAB_010385aa;
          }
          iVar2 = *(volatile int*)(param_1+0x10) + 0x14;
          break;
        case 8:
          if (*(volatile int*)(param_1+0x10) == 0) {
            FUN_01039bbe(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103eb7f) /*=0x103eb7f*/, 0x99u);
            uVar8 = 0x99; uVar3 = ((unsigned long)&rodata_103eb7f) /*=0x103eb7f*/;
            goto LAB_010385aa;
          }
          iVar2 = *(volatile int*)(param_1+0x10) + 0x28;
          break;
        default:
          FUN_01039bbe(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103eb7f) /*=0x103eb7f*/, 0xa6u);
          uVar8 = 0xa6; uVar3 = ((unsigned long)&rodata_103eb7f) /*=0x103eb7f*/;
          goto LAB_010385aa;
      }
      FUN_0103b3e0(iVar2, param_1, param_3);
    caseD_0:
      *(volatile char**)(param_1+8) = param_3;
      iVar7 = iVar7 + 1;
    }
  LAB_01038536:
    iVar2 = FUN_01036128(uVar3);
    param_1 = param_1 + 0x14;
    if (iVar2 == 0) {
      FUN_01039bbe(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/, 0xf0u);
      uVar8 = 0xf0; uVar3 = ((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/;
    LAB_010385aa:
      /* Shared abort trampoline: real hardware never returns from this call
         (panic), but the parity harness always "returns" a mocked value, so
         execution falls through into the code-layout-adjacent case-4 tail
         (uVar5=4; goto LAB_0103851c) exactly as the compiled binary does. */
      FUN_01039bb0(uVar3, uVar8);
      uVar5 = 4;
      goto LAB_0103851c;
    }
    if (isCurrentModePrivileged()) setBasePriority(uVar8);
    InstructionSynchronizationBarrier(0xf);
    iVar6 = iVar6 + 1;
  }
}
