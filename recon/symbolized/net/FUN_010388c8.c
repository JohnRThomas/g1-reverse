#include "g1_net_symbols.h"
/* net-core FUN_010388c8 @ 0x10388c8  (parity 300 trials PROVEN) */
static inline unsigned int getBasePriority(void){unsigned b;__asm__ volatile("mrs %0, basepri":"=r"(b));return b;}
static inline void setBasePriority(unsigned p){__asm__ volatile("msr basepri, %0"::"r"(p):"memory");}
static inline void isb(void){__asm__ volatile("isb":::"memory");}

#define C_0103894c ((uintptr_t)&g_net_poll_signal_lock) /*=0x21004b78*/
#define C_01038950 "***** HARD FAULT *****" /*=0x103d3b6*/
#define C_01038954 "acking error (context area might be not valid)" /*=0x103d2a7*/

extern int FUN_0103610c(int);
extern void FUN_01036144(int);
extern int FUN_01036128(int);
extern void FUN_01039bbe(int, int, unsigned int);
extern void FUN_01039bb0(int, unsigned int);
extern int FUN_0103b442(void);
extern void FUN_01037130(int, unsigned int);

int FUN_010388c8(int *param_1, int param_2)
{
  unsigned int r6;
  int r0;
  int r1;
  unsigned int r2;
  int *piVar4;
  int iVar3;
  int *piVar5;
  int uVar6;

  r6 = getBasePriority();
  setBasePriority(0x40);
  isb();
  r0 = FUN_0103610c(C_0103894c);
  if (r0 != 0) goto L8f8;

  r1 = C_01038950;
  r2 = 0x72;
  FUN_01039bbe(C_01038954, r1, r2);
  r1 = 0x72;

L8f2:
  r0 = C_01038950;
  FUN_01039bb0(r0, (unsigned int)r1);
  goto L8f8;

L8f8:
  FUN_01036144(C_0103894c);
  piVar4 = (int *)*param_1;
  param_1[3] = param_2;
  param_1[2] = 1;
  if (param_1 == piVar4) {
    r0 = FUN_01036128(C_0103894c);
    if (r0 == 0) {
      r1 = C_01038950;
      r2 = 0xf0;
      FUN_01039bbe(C_01038954, r1, r2);
      r1 = 0xf0;
      goto L8f2;
    }
    setBasePriority(r6);
    isb();
    return 0;
  } else {
    iVar3 = *piVar4;
    piVar5 = (int *)piVar4[1];
    *piVar5 = iVar3;
    *(int **)(iVar3 + 4) = piVar5;
    *piVar4 = 0;
    piVar4[1] = 0;
    uVar6 = FUN_0103b442();
    FUN_01037130(C_0103894c, r6);
    return uVar6;
  }
}

