/* Reconstructed FUN_00056080 @ 0x56080  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
typedef int (*fnptr_t)(int,int,int);
extern void FUN_0007e2fa(unsigned long, ...);
extern unsigned long long FUN_0007e2ec(int a,int b);
extern void FUN_00086502(int a);
void FUN_00056080(int param_1, int param_2)
{
  fnptr_t UNRECOVERED_JUMPTABLE;
  int uVar1;
  if (param_2 == 0) {
    FUN_0007e2fa(0x99cbd, 0xf3aa8, 0xf3a5d, 0x46);
    param_2 = (int)(FUN_0007e2ec(0xf3a5d, 0x46) >> 32);
  }
  UNRECOVERED_JUMPTABLE = (fnptr_t)*(volatile uint32_t *)(param_2 + 4);
  uVar1 = *(volatile int *)(param_2 + 8);
  *(volatile int *)(param_2 + 0xc) = 0;
  *(volatile int *)(param_2 + 4) = 0;
  *(volatile int *)(param_2 + 8) = 0;
  FUN_00086502(0x20003a60);
  (*UNRECOVERED_JUMPTABLE)(param_1, uVar1, 0xffffff92);
}
