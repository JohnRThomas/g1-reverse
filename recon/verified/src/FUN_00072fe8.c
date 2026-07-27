/* Reconstructed FUN_00072fe8 @ 0x72fe8  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int FUN_00072040(uint32_t);
extern int FUN_0007205c(uint32_t);
extern void FUN_00072078(uint32_t);
extern void FUN_0007e2ec(uint32_t,uint32_t);
extern void FUN_0007e2fa(unsigned long, ...);
extern uint32_t FUN_00086596(int);

uint32_t FUN_00072fe8(int param_1, uint32_t param_2, uint32_t param_3, uint32_t param_4){
  uint32_t sb, uVar4;
  int iVar3;
  if (param_1 == 0){
    FUN_0007e2fa(0x99cbd,0xf82e0,0xf820f,0x221,param_4);
    FUN_0007e2ec(0xf820f,0x221);
  }
  if ((int32_t)((uint32_t)*(int*)(param_1+0xc) << 0x17) < 0){
    FUN_0007e2fa(0x99cbd,0xf8262,0xf820f,0x222,param_4);
    FUN_0007e2ec(0xf820f,0x222);
  }
  __asm volatile("mrs %0, basepri" : "=r"(sb));
  __asm volatile("msr basepri_max, %0" :: "r"((uint32_t)0x20));
  __asm volatile("isb sy");
  iVar3 = FUN_00072040(0x2000b480);
  if (iVar3 == 0){
    FUN_0007e2fa(0x99cbd,0xf0920,0xf08c7,0x72,param_4);
    FUN_0007e2fa(0xf0935,0x2000b480);
    FUN_0007e2ec(0xf08c7,0x72);
  }
  FUN_00072078(0x2000b480);
  uVar4 = FUN_00086596(param_1);
  iVar3 = FUN_0007205c(0x2000b480);
  if (iVar3 == 0){
    FUN_0007e2fa(0x99cbd,0xf08f4,0xf08c7,0xf0,param_4);
    FUN_0007e2fa(0xf090b,0x2000b480);
    FUN_0007e2ec(0xf08c7,0xf0);
  }
  __asm volatile("msr basepri, %0" :: "r"(sb));
  __asm volatile("isb sy");
  return uVar4;
}

