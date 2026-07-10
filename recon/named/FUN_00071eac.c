/* named: FUN_00071eac */
/* Reconstructed FUN_00071eac @ 0x71eac  (parity: 80/80 trials, PROVEN) */
#include <stdint.h>
extern void FUN_00071df8(void);
extern void sched_thread_ready(int);
extern void FUN_00074bf4(int,unsigned int,int,int,int,int,int,int,int,unsigned int);
int FUN_00071eac(int param_1,int p2,int p3,int p4,int s0,int s1,int s2,int s3,int s4,int s5,int s6,int s7){
  unsigned int uVar2=0;
  FUN_00071df8();
  if(s7!=-1 || s6!=-1){
    if(s7==0 && s6==0){
      sched_thread_ready(param_1);
    } else {
      FUN_00074bf4(param_1+0x18,0x00086661,s6,s7,s0,s1,s2,s3,s4,uVar2);
    }
  }
  return param_1;
}

