/* Reconstructed FUN_00058eb0 @ 0x58eb0  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int FUN_0005858c(unsigned long);
extern int FUN_000585f0(void*,int,int);
extern void FUN_00081ddc(int,int,void*);
int FUN_00058eb0(int param_1,int param_2,int param_3){
  int iVar1=FUN_0005858c(param_1);
  if(iVar1==0) return 0;
  int *piVar2,*piVar5,*piVar6;
  unsigned int uStack_20; unsigned int uVar4;
  piVar5=*(int**)(iVar1+0x30);
  if(piVar5==0){ piVar2=0; piVar5=0; }
  else { piVar2=piVar5-100; piVar5=(int*)*piVar5; if(piVar5!=0) piVar5=piVar5-100; }
  uStack_20=param_3+1;
  if(piVar2!=0){
    while(1){
      piVar6=piVar5;
      uVar4=*(uint16_t*)((int)piVar2+0x1e);
      if(*(uint16_t*)((int)piVar2+0x2e) <= *(uint16_t*)((int)piVar2+0x1e)) uVar4=*(uint16_t*)((int)piVar2+0x2e);
      if(uStack_20<=uVar4){ return FUN_000585f0(piVar2,param_2,param_3); }
      if(piVar6==0) break;
      piVar5=(int*)piVar6[100]; piVar2=piVar6; if(piVar5!=0) piVar5=piVar5-100;
    }
  }
  int local_28[4];
  local_28[0]=3; local_28[1]=0xf4636; local_28[2]=uStack_20;
  FUN_00081ddc(0x88100,0x1880,local_28);
  return 0;
}

