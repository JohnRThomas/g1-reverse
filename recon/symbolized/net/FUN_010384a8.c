#include "g1_net_symbols.h"
/* net-core FUN_010384a8 @ 0x10384a8  (parity 147 trials PROVEN) */
typedef unsigned int uint;
static inline int isCurrentModePrivileged(void){unsigned c;__asm__ volatile("mrs %0, control":"=r"(c));return (c&1)==0;}
static inline int getBasePriority(void){unsigned b;__asm__ volatile("mrs %0, basepri":"=r"(b));return (int)b;}
static inline void setBasePriority(int p){__asm__ volatile("msr basepri, %0"::"r"(p):"memory");}
static inline void InstructionSynchronizationBarrier(int x){(void)x;__asm__ volatile("isb":::"memory");}

extern int FUN_0103610c(unsigned int);
extern int FUN_01036128(unsigned int);
extern void FUN_01036144(unsigned int);
extern void FUN_01039bb0(unsigned int, unsigned int);
extern void FUN_01039bbe(unsigned int, unsigned int, unsigned int);
extern void FUN_0103b3e0(int, int, char*);

int FUN_010384a8(int param_1,int param_2,char *param_3,int param_4)
{
  unsigned int uVar3 = ((uintptr_t)&g_net_poll_signal_lock) /*=0x21004b78*/;
  int iVar6 = 0, iVar7 = 0;
  int p1 = param_1;

  while (iVar6 < param_2) {
    unsigned int uVar8 = 0;
    if (isCurrentModePrivileged()) uVar8 = getBasePriority();
    if (isCurrentModePrivileged()) {
        unsigned int uVar5 = getBasePriority();
        if (uVar5 == 0 || uVar5 > 0x40) setBasePriority(0x40);
    }
    InstructionSynchronizationBarrier(0xf);

    int iVar2 = FUN_0103610c(uVar3);
    if (iVar2 == 0) {
      FUN_01039bbe("acking error (context area might be not valid)" /*=0x103d2a7*/, "***** HARD FAULT *****" /*=0x103d3b6*/, 0x72u);
      FUN_01039bb0("***** HARD FAULT *****" /*=0x103d3b6*/, 0x72u);
      __builtin_unreachable();
    }
    FUN_01036144(uVar3);
    unsigned char bVar4 = *(volatile unsigned char *)(p1 + 0xd) & 0x3f;
    unsigned int uVar5v = 0;
    int didSet = 0;
    switch (bVar4) {
      case 0: break;
      case 1:
        if (*(volatile int*)(*(volatile int*)(p1+0x10) + 8) != 0) { uVar5v = 1; didSet = 1; }
        break;
      case 2:
        if (*(volatile int*)(*(volatile int*)(p1+0x10) + 8) != 0) { uVar5v = 2; didSet = 1; }
        break;
      case 4:
        if (*(volatile int*)(*(volatile int*)(p1+0x10)) != 0) { uVar5v = 4; didSet = 1; }
        break;
      case 8:
        if (*(volatile int*)(*(volatile int*)(p1+0x10) + 0x24) != 0) { uVar5v = 0x10; didSet = 1; }
        break;
      default:
        FUN_01039bbe("acking error (context area might be not valid)" /*=0x103d2a7*/, ((uintptr_t)&rodata_103eb7f) /*=0x103eb7f*/, 0x63u);
        FUN_01039bb0(((uintptr_t)&rodata_103eb7f) /*=0x103eb7f*/, 0x63u);
        __builtin_unreachable();
    }
    if (didSet) {
      *(volatile int*)(p1+8) = 0;
      unsigned int c = *(volatile unsigned int*)(p1+0xc);
      unsigned int nb = uVar5v | ((c << 0xb) >> 0x19);
      *(volatile unsigned int*)(p1+0xc) = (c & 0xffe03fffu) | (nb << 0xe);
      *param_3 = '\0';
    } else {
      if (param_4 == 0 && *param_3 != 0) {
        unsigned char bVar4b = *(volatile unsigned char *)(p1 + 0xd) & 0x3f;
        int iVar2b = 0;
        int writeDirect = 0;
        switch (bVar4b) {
          case 0:
            writeDirect = 1;
            break;
          case 1:
            iVar2b = *(volatile int*)(p1+0x10);
            if (iVar2b == 0) {
              FUN_01039bbe("acking error (context area might be not valid)" /*=0x103d2a7*/, ((uintptr_t)&rodata_103eb7f) /*=0x103eb7f*/, 0x95u);
              FUN_01039bb0(((uintptr_t)&rodata_103eb7f) /*=0x103eb7f*/, 0x95u);
              __builtin_unreachable();
            }
            break;
          case 2:
            if (*(volatile int*)(p1+0x10) == 0) {
              FUN_01039bbe("acking error (context area might be not valid)" /*=0x103d2a7*/, ((uintptr_t)&rodata_103eb7f) /*=0x103eb7f*/, 0x8du);
              FUN_01039bb0(((uintptr_t)&rodata_103eb7f) /*=0x103eb7f*/, 0x8du);
              __builtin_unreachable();
            }
            iVar2b = *(volatile int*)(p1+0x10) + 0x10;
            break;
          case 4:
            if (*(volatile int*)(p1+0x10) == 0) {
              FUN_01039bbe("acking error (context area might be not valid)" /*=0x103d2a7*/, ((uintptr_t)&rodata_103eb7f) /*=0x103eb7f*/, 0x91u);
              FUN_01039bb0(((uintptr_t)&rodata_103eb7f) /*=0x103eb7f*/, 0x91u);
              __builtin_unreachable();
            }
            iVar2b = *(volatile int*)(p1+0x10) + 0x14;
            break;
          case 8:
            if (*(volatile int*)(p1+0x10) == 0) {
              FUN_01039bbe("acking error (context area might be not valid)" /*=0x103d2a7*/, ((uintptr_t)&rodata_103eb7f) /*=0x103eb7f*/, 0x99u);
              FUN_01039bb0(((uintptr_t)&rodata_103eb7f) /*=0x103eb7f*/, 0x99u);
              __builtin_unreachable();
            }
            iVar2b = *(volatile int*)(p1+0x10) + 0x28;
            break;
          default:
            FUN_01039bbe("acking error (context area might be not valid)" /*=0x103d2a7*/, ((uintptr_t)&rodata_103eb7f) /*=0x103eb7f*/, 0xa6u);
            FUN_01039bb0(((uintptr_t)&rodata_103eb7f) /*=0x103eb7f*/, 0xa6u);
            __builtin_unreachable();
        }
        if (!writeDirect) {
          FUN_0103b3e0(iVar2b, p1, param_3);
        }
        *(volatile char**)(p1+8) = param_3;
        iVar7 = iVar7 + 1;
      }
    }
    int iVar2c = FUN_01036128(uVar3);
    p1 = p1 + 0x14;
    if (iVar2c == 0) {
      FUN_01039bbe("acking error (context area might be not valid)" /*=0x103d2a7*/, "***** HARD FAULT *****" /*=0x103d3b6*/, 0xf0u);
      FUN_01039bb0("***** HARD FAULT *****" /*=0x103d3b6*/, 0xf0u);
      __builtin_unreachable();
    }
    if (isCurrentModePrivileged()) setBasePriority(uVar8);
    InstructionSynchronizationBarrier(0xf);
    iVar6 = iVar6 + 1;
  }
  return iVar7;
}

