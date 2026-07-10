/* Reconstructed FUN_000739f0 @ 0x739f0  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_0007205c(int);
extern void FUN_000501d4(int);
extern void FUN_0007e2ec(int,int);
extern void FUN_0007e2fa(int,...);
void FUN_000739f0(int param_1, int param_2){
  unsigned int r6;
  int r0v;
  if(param_2 == 0){
    __asm volatile("mrs %0, ipsr" : "=r"(r6));
    if(r6 == 0){
      volatile int *g = (volatile int*)0x2000b448UL;
      if(g[6] != g[2]){
        r0v = FUN_0007205c(param_1);
        if(r0v != 0){ FUN_000501d4(r6); return; }
        FUN_0007e2fa(0x99cbd, 0xf08f4, 0xf08c7, 0x111);
        FUN_0007e2fa(0xf090b, param_1);
        FUN_0007e2ec(0xf08c7, 0x111);
        return;
      }
    }
  }
  r0v = FUN_0007205c(param_1);
  if(r0v != 0){
    __asm volatile("msr basepri, %0" :: "r"(param_2));
    __asm volatile("isb");
    return;
  }
  FUN_0007e2fa(0x99cbd, 0xf08f4, 0xf08c7, 0xf0);
  FUN_0007e2fa(0xf090b, param_1);
  FUN_0007e2ec(0xf08c7, 0xf0);
}

