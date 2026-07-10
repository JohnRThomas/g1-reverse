#include "g1_net_symbols.h"
/* net-core FUN_010378c4 @ 0x10378c4  (parity 300 trials PROVEN) */
static inline unsigned int getBasePriority(void){unsigned b;__asm__ volatile("mrs %0, basepri":"=r"(b));return b;}
static inline void setBasePriority(unsigned p){__asm__ volatile("msr basepri, %0"::"r"(p):"memory");}
static inline void isb(void){__asm__ volatile("isb":::"memory");}

#define C_01037954 ((uintptr_t)&g_zephyr_sched_spinlock) /*=0x21004b68*/
#define C_01037958 "***** HARD FAULT *****" /*=0x103d3b6*/
#define C_0103795c "acking error (context area might be not valid)" /*=0x103d2a7*/

extern int FUN_0103610c(int);
extern void FUN_01036144(int);
extern int FUN_01036128(int);
extern void FUN_01039bbe(int, int, unsigned int);
extern void FUN_01039bb0(int, unsigned int);
extern void FUN_01037814(int);
extern void FUN_01036fcc(int);

void FUN_010378c4(int param_1, int param_2)
{
  unsigned int r6;
  int r0;
  int r1;
  unsigned char cVar1;
  unsigned char bVar5;

  r6 = getBasePriority();
  setBasePriority(0x40);
  isb();
  r0 = FUN_0103610c(C_01037954);
  if (r0 != 0) goto L8f4;

  r1 = C_01037958;
  FUN_01039bbe(C_0103795c, r1, 0x72);
  r1 = 0x72;
  r0 = C_01037958;
L_abortcall:
  FUN_01039bb0(r0, (unsigned int)r1);
  goto L8f4;

L8f4:
  FUN_01036144(C_01037954);
  cVar1 = *(unsigned char *)(param_1 + 0x70);
  *(unsigned char *)(param_1 + 0x70) = 0;
  if ((cVar1 == 0 || param_2 == 0) && ((*(unsigned char *)(param_1 + 0xd) & 0x28) == 0)) {
    if (*(int *)(param_1 + 8) != 0) {
      FUN_01037814(param_1);
    }
    if (param_2 == 0) {
      bVar5 = *(unsigned char *)(param_1 + 0xd) & 0xfb;
    } else {
      bVar5 = *(unsigned char *)(param_1 + 0xd) & 0xeb;
    }
    *(unsigned char *)(param_1 + 0xd) = bVar5;
    FUN_01036fcc(param_1);
  }
  r0 = FUN_01036128(C_01037954);
  if (r0 != 0) {
    setBasePriority(r6);
    isb();
    return;
  }
  r1 = C_01037958;
  FUN_01039bbe(C_0103795c, r1, 0xf0);
  r1 = 0xf0;
  r0 = C_01037958;
  goto L_abortcall;
}

