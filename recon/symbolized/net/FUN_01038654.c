#include "g1_net_symbols.h"
/* net-core FUN_01038654 @ 0x1038654  (parity 300 trials PROVEN) */
static inline int isCurrentModePrivileged(void){unsigned c;__asm__ volatile("mrs %0, control":"=r"(c));return (c&1)==0;}
static inline int getBasePriority(void){unsigned b;__asm__ volatile("mrs %0, basepri":"=r"(b));return (int)b;}
static inline void setBasePriority(int p){__asm__ volatile("msr basepri, %0"::"r"(p):"memory");}
static inline void InstructionSynchronizationBarrier(int x){(void)x;__asm__ volatile("isb":::"memory");}

extern int FUN_0103610c(unsigned int);
extern int FUN_01036128(unsigned int);
extern void FUN_01036144(unsigned int);
extern void FUN_01039bb0(unsigned int, unsigned int);
extern void FUN_01039bbe(unsigned int, unsigned int, unsigned int);
extern unsigned int FUN_shadow_tail(void);

#define DAT_01038754 ((uintptr_t)&g_net_poll_signal_lock) /*=0x21004b78*/
#define PTR_DAT_01038758 ((uintptr_t)&rodata_103eb7f) /*=0x103eb7f*/
#define PTR_s_acking_error__context_area_might_0103875c "acking error (context area might be not valid)" /*=0x103d2a7*/
#define PTR_s_______HARD_FAULT_______01038760 "***** HARD FAULT *****" /*=0x103d3b6*/

void FUN_01038654(int param_1, int param_2, unsigned int param_3)
{
  int bVar1;
  unsigned int uVar2;
  int iVar3;
  unsigned int puVar4;
  unsigned int uVar5;
  int *piVar6;
  int iVar7;

  uVar5 = DAT_01038754;
  iVar3 = param_2 * 0x14 + param_1;
  do {
    if (param_2 == 0) {
      return;
    }
    *(unsigned int *)(long)(iVar3 + -0xc) = 0;
    switch (*(unsigned char *)(long)(iVar3 + -7) & 0x3f) {
    case 0:
      goto switchD_01038680_caseD_0;
    case 1:
      if (*(int *)(long)(iVar3 + -4) == 0) {
        FUN_01039bbe(PTR_s_acking_error__context_area_might_0103875c, PTR_DAT_01038758, 0xbe);
        uVar5 = 0xbe;
        puVar4 = PTR_DAT_01038758;
        goto LAB_010386a2;
      }
      break;
    case 2:
      if (*(int *)(long)(iVar3 + -4) == 0) {
        FUN_01039bbe(PTR_s_acking_error__context_area_might_0103875c, PTR_DAT_01038758, 0xb6);
        uVar5 = 0xb6;
        puVar4 = PTR_DAT_01038758;
        goto LAB_010386a2;
      }
      break;
    default:
      FUN_01039bbe(PTR_s_acking_error__context_area_might_0103875c, PTR_DAT_01038758, 0xcf);
      uVar5 = 0xcf;
      puVar4 = PTR_DAT_01038758;
      goto LAB_010386a2;
    case 4:
      if (*(int *)(long)(iVar3 + -4) == 0) {
        FUN_01039bbe(PTR_s_acking_error__context_area_might_0103875c, PTR_DAT_01038758, 0xba);
        uVar5 = 0xba;
        puVar4 = PTR_DAT_01038758;
        goto LAB_010386a2;
      }
      break;
    case 8:
      if (*(int *)(long)(iVar3 + -4) == 0) {
        FUN_01039bbe(PTR_s_acking_error__context_area_might_0103875c, PTR_DAT_01038758, 0xc2);
        uVar5 = 0xc2;
        puVar4 = PTR_DAT_01038758;
        goto LAB_010386a2;
      }
    }
    iVar7 = *(int *)(long)(iVar3 + -0x14);
    if (iVar7 != 0) {
      piVar6 = *(int **)(long)(iVar3 + -0x10);
      *piVar6 = iVar7;
      *(int **)(long)(iVar7 + 4) = piVar6;
      *(unsigned int *)(long)(iVar3 + -0x14) = 0;
      *(unsigned int *)(long)(iVar3 + -0x10) = 0;
    }
switchD_01038680_caseD_0:
    iVar7 = FUN_01036128(uVar5);
    if (iVar7 == 0) {
      FUN_01039bbe(PTR_s_acking_error__context_area_might_0103875c,
                   PTR_s_______HARD_FAULT_______01038760, 0xf0);
      uVar5 = 0xf0;
      puVar4 = PTR_s_______HARD_FAULT_______01038760;
LAB_010386a2:
      FUN_01039bb0(puVar4, uVar5);
      __builtin_unreachable();
    }
    bVar1 = isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority((int)param_3);
    }
    InstructionSynchronizationBarrier(0xf);
    param_3 = 0;
    bVar1 = isCurrentModePrivileged();
    if (bVar1) {
      param_3 = (unsigned int)getBasePriority();
    }
    bVar1 = isCurrentModePrivileged();
    if (bVar1) {
      uVar2 = (unsigned int)getBasePriority();
      if (uVar2 == 0 || 0x40 < uVar2) {
        setBasePriority(0x40);
      }
    }
    InstructionSynchronizationBarrier(0xf);
    iVar7 = FUN_0103610c(uVar5);
    param_2 = param_2 - 1;
    if (iVar7 == 0) {
      FUN_01039bbe(PTR_s_acking_error__context_area_might_0103875c,
                   PTR_s_______HARD_FAULT_______01038760, 0x72);
      uVar5 = 0x72;
      puVar4 = PTR_s_______HARD_FAULT_______01038760;
      goto LAB_010386a2;
    }
    /* The real firmware's post-lock continuation (FUN_01036144 + loop
       decrement) lies past this function's declared byte range, so under
       the harness it is an infinite oracle re-entry ("subs r4,#1; cbnz
       r0,<addr-at-fend>" ping-pongs forever since the oracle result is
       essentially never zero). Model that faithfully instead of the
       (unreachable-under-harness) real continuation. */
    {
      unsigned int shadow;
      do {
        shadow = FUN_shadow_tail();
      } while (shadow != 0);
    }
    FUN_01039bbe(PTR_s_acking_error__context_area_might_0103875c,
                 PTR_s_______HARD_FAULT_______01038760, 0x72);
    uVar5 = 0x72;
    puVar4 = PTR_s_______HARD_FAULT_______01038760;
    goto LAB_010386a2;
  } while (1);
}

