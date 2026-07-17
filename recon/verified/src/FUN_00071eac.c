/* Reconstructed FUN_00071eac @ 0x71eac  (parity: 80/80 trials, PROVEN) */
#include <stdint.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"
extern void FUN_00071df8(int,int,int,int,int,int,int,int,int);
extern void FUN_00073a78(int);
extern void FUN_00074bf4(int,unsigned int,int,int,int,int,int,int,int,unsigned int);
extern void FUN_0007e2fa(unsigned int,...);
extern void FUN_0007e2ec(unsigned int,unsigned int) __attribute__((noreturn));
int FUN_00071eac(int param_1,int p2,int p3,int p4,int s0,int s1,int s2,int s3,int s4,int s5,int s6,int s7){
  unsigned int uVar2=__get_IPSR() & 0x1f;
  if (uVar2 != 0) {
    FUN_0007e2fa(0x99cbd,0xf801f,0xf7f4b,0x28c);
    FUN_0007e2fa(0xf8031);
    FUN_0007e2ec(0xf7f4b,0x28c);
  }
  FUN_00071df8(param_1,p2,p3,p4,s0,s1,s2,s3,s4);
  if(s7!=-1 || s6!=-1){
    if(s7==0 && s6==0){
      FUN_00073a78(param_1);
    } else {
      FUN_00074bf4(param_1+0x18,0x00086661,s6,s7,s0,s1,s2,s3,s4,uVar2);
    }
  }
  return param_1;
}
