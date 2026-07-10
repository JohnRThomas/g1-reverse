/* Reconstructed FUN_00073ec0 @ 0x73ec0  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void FUN_00073e88(void);
extern void FUN_0007e2ec(uint32_t,uint32_t);
extern void FUN_0007e2fa(uint32_t,uint32_t,uint32_t,uint32_t,uint32_t);
void FUN_00073ec0(volatile int *param_1, volatile int *param_2, uint32_t param_3, uint32_t param_4){
  volatile int *piVar1,*piVar2;
  FUN_00073e88();
  *(volatile uint8_t*)((int)param_1+0xd) = *(volatile uint8_t*)((int)param_1+0xd) | 2;
  piVar2=(volatile int*)0x20006720;
  if(param_2!=0){
    param_1[2]=(int)param_2;
    if(param_1==piVar2){
      FUN_0007e2fa(0x99cbd,0xf84d6,0xf82f4,0xc1,param_4);
      FUN_0007e2ec(0xf82f4,0xc1);
    }
    piVar2=(volatile int*)*param_2;
    if(param_2!=piVar2){
      for(;piVar2!=0;piVar2=(volatile int*)*piVar2){
        if((*(volatile int8_t*)((int)param_1+0xe)!=*(volatile int8_t*)((int)piVar2+0xe)) &&
           (*(volatile int8_t*)((int)param_1+0xe) < *(volatile int8_t*)((int)piVar2+0xe))){
          piVar1=(volatile int*)piVar2[1];
          *param_1=(int)piVar2;
          param_1[1]=(int)piVar1;
          *piVar1=(int)param_1;
          piVar2[1]=(int)param_1;
          return;
        }
        if(piVar2==(volatile int*)param_2[1]) break;
      }
    }
    piVar2=(volatile int*)param_2[1];
    *param_1=(int)param_2;
    param_1[1]=(int)piVar2;
    *piVar2=(int)param_1;
    param_2[1]=(int)param_1;
  }
}

