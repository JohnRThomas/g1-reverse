/* Reconstructed FUN_00074844 @ 0x74844  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_000741a4(int);
extern int FUN_000746fc(void);
extern int FUN_0007e2ec(int,int);
extern int FUN_0007e2fa(int,...);
uint32_t FUN_00074844(int param_1,int param_2,int param_3,int param_4){
  uint32_t ipsr;
  __asm volatile("mrs %0, ipsr":"=r"(ipsr));
  if(ipsr != 0){
    FUN_0007e2fa(0x00099cbd, 0x000f801f, 0x000f82f4, 0x5c1, param_4);
    FUN_0007e2fa(0x000f53ff);
    FUN_0007e2ec(0x000f82f4, 0x5c1);
  }
  if(param_2==-1 && param_1==-1){
    FUN_000741a4(*(volatile int*)(0x2000b448UL+8));
    return 0xffffffff;
  }
  int iVar2 = FUN_000746fc();
  return (uint32_t)(((int64_t)iVar2 * 1000) >> 15);
}

