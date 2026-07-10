/* Reconstructed FUN_00076cec @ 0x76cec  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int FUN_00086b7e(int,void*,void*,void*);
extern int FUN_00076e20(int,int);
extern int FUN_00078570(int,int);
void FUN_00076cec(int param_1,int *param_2,int param_3){
  if(-1 < (int)((unsigned)*(uint16_t*)((int)param_2+0xc) << 0x1e)){
    int local_20=param_1; int *local_1c=param_2; int uStack_18=param_3;(void)uStack_18;
    unsigned uVar1=FUN_00086b7e(param_1,param_2,&local_20,&local_1c);
    int iVar3=local_20;
    int iVar2=FUN_00076e20(param_1,local_20);
    if(iVar2!=0){
      *(volatile int*)(param_1+0x28)=0x76b91;
      *(volatile int*)((int)param_2)=iVar2;
      *(volatile uint16_t*)((int)param_2+0xc) |= 0x80;
      *(volatile int*)((int)param_2+0x10)=iVar2;
      *(volatile int*)((int)param_2+0x14)=iVar3;
      if(local_1c!=0){
        int t=FUN_00078570(param_1,(int)*(int16_t*)((int)param_2+0xe));
        if(t!=0){ *(volatile uint16_t*)((int)param_2+0xc)=(*(volatile uint16_t*)((int)param_2+0xc)&0xfffc)|1; }
      }
      *(volatile uint16_t*)((int)param_2+0xc) = (uint16_t)(uVar1 | *(volatile uint16_t*)((int)param_2+0xc));
      return;
    }
    if((int)((int16_t)*(uint16_t*)((int)param_2+0xc))<<0x16 < 0) return;
    *(volatile uint16_t*)((int)param_2+0xc)=(*(volatile uint16_t*)((int)param_2+0xc)&0xfffc)|2;
  }
  *(volatile int*)((int)param_2)=(int)param_2+0x47;
  *(volatile int*)((int)param_2+0x10)=(int)param_2+0x47;
  *(volatile int*)((int)param_2+0x14)=1;
}

