/* Reconstructed FUN_00072558 @ 0x72558  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"
extern void FUN_0007e2fa(unsigned,unsigned,unsigned,unsigned);
extern void FUN_0007e2ec(unsigned,unsigned);
extern int FUN_00072040(unsigned);
extern int FUN_0007205c(unsigned);
extern void FUN_00072078(unsigned);
extern void FUN_000738d4(void);
extern void FUN_000739f0(unsigned,unsigned);
extern int FUN_000744a4(int);
extern void FUN_000864b2(unsigned,unsigned);
unsigned FUN_00072558(int param_1)
{
  unsigned ipsr, basepri; int iVar4, r3;
  ipsr = __get_IPSR();
  if (ipsr != 0) {
    FUN_0007e2fa(0x00099cbd,0x000f801f,0x000f813a,0xcd);
    FUN_0007e2fa(0x000f815c,0,0,0);
    FUN_0007e2ec(0x000f813a,0xcd);
  }
  r3 = *(int*)(param_1+8);
  if (r3 == 0) return 0xffffffea;
  if (r3 != *(int*)(0x2000b448+8)) return 0xffffffff;
  iVar4 = *(int*)(param_1+0xc);
  if (iVar4 == 0) {
    FUN_0007e2fa(0x00099cbd,0x000f8181,0x000f813a,0xe5);
    FUN_0007e2ec(0x000f813a,0xe5);
  }
  if (iVar4 != 1) {
    *(volatile int*)(param_1+0xc) = iVar4 - 1;
    return 0;
  }
  basepri = __get_BASEPRI();
  __set_BASEPRI_MAX(0x20u);
  __ISB();
  iVar4 = FUN_00072040(0x2000b470);
  if (iVar4 == 0) {
    FUN_0007e2fa(0x00099cbd,0x000f0920,0x000f08c7,0x72);
    FUN_0007e2fa(0x000f0935,0x2000b470,0,0);
    FUN_0007e2ec(0x000f08c7,0x72);
  }
  FUN_00072078(0x2000b470);
  FUN_000864b2(*(unsigned*)(param_1+8), *(unsigned*)(param_1+0x10));
  iVar4 = FUN_000744a4(param_1);
  *(volatile int*)(param_1+8) = iVar4;
  if (iVar4 == 0) {
    *(volatile int*)(param_1+0xc) = 0;
    iVar4 = FUN_0007205c(0x2000b470);
    if (iVar4 == 0) {
      FUN_0007e2fa(0x00099cbd,0x000f08f4,0x000f08c7,0xf0);
      FUN_0007e2fa(0x000f090b,0x2000b470,0,0);
      FUN_0007e2ec(0x000f08c7,0xf0);
    }
    __set_BASEPRI(basepri);
    __ISB();
  } else {
    *(volatile int*)(param_1+0x10) = (int)*(signed char*)(iVar4+0xe);
    *(volatile unsigned*)(iVar4+0x90) = ipsr;
    FUN_000738d4();
    FUN_000739f0(0x2000b470, basepri);
  }
  return 0;
}
