/* Reconstructed FUN_00072880 @ 0x72880  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_00072040(int);
extern void FUN_00072078(int);
extern void FUN_000738d4(void);
extern void FUN_000739f0(int,int);
extern int FUN_000744a4(int);
extern void FUN_0007e2ec(int,int);
extern void FUN_0007e2fa(int,...);
extern void FUN_0008688e(int,int);
void FUN_00072880(int param_1, int param_2, int param_3, int param_4){
  unsigned int r5;
  int r3v = 0x20;
  __asm volatile("mrs %0, basepri" : "=r"(r5));
  __asm volatile("msr basepri_max, %0" :: "r"(r3v));
  __asm volatile("isb");
  int r0 = FUN_00072040(0x2000b474);
  if(r0 == 0){
    FUN_0007e2fa(0x99cbd, 0xf0920, 0xf08c7, 0x72);
    FUN_0007e2fa(0xf0935, 0x2000b474);
    FUN_0007e2ec(0xf08c7, 0x72);
    return;
  }
  FUN_00072078(0x2000b474);
  int r0b = FUN_000744a4(param_1);
  if(r0b == 0){
    int a = *(volatile int*)(param_1+8);
    int b = *(volatile int*)(param_1+0xc);
    if(b != a) a = a + 1;
    *(volatile int*)(param_1+8) = a;
    FUN_0008688e(param_1+0x10, 2);
  } else {
    *(volatile int*)(r0b + 0x90) = 0;
    FUN_000738d4();
  }
  FUN_000739f0(0x2000b474, r5);
}

