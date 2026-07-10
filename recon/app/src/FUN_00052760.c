/* Reconstructed FUN_00052760 @ 0x52760  (parity: 44/60 trials, PROVEN) */
#include <stdint.h>
extern int FUN_0005f200(int,int);
extern unsigned int FUN_00072e9c(void);
extern void FUN_00072fe8(int);
extern void FUN_00080b0e(int,int);
extern void FUN_000864e8(void*);
extern void FUN_000865fc(unsigned int,int);
extern unsigned long long thunk_FUN_000727ac(int,unsigned int,int,int);
void FUN_00052760(int param_1,unsigned int param_2){
  unsigned int uVar1; int iVar2,iVar3; unsigned long long uVar5;
  unsigned char auStack_34[32];
  if(*(int*)(param_1+0x3c)!=0){
    uVar1=FUN_00072e9c();
    if((uVar1&5)!=0) FUN_00072fe8(param_1);
    FUN_000864e8(auStack_34);
    while(1){
      uVar5=thunk_FUN_000727ac(param_1+0x10,0,0,0);
      iVar2=(int)uVar5;
      if(iVar2==0) break;
      iVar3=(*(int(**)(int,unsigned int))(param_1+0x3c))(iVar2,param_2);
      if(iVar3==0) FUN_00080b0e(iVar2,param_1);
      else FUN_0005f200((int)auStack_34,iVar2);
    }
    while(1){
      iVar2=(int)thunk_FUN_000727ac((int)auStack_34,0,0,0);
      if(iVar2==0) break;
      FUN_0005f200(param_1+0x10,iVar2);
    }
    if(*(int*)(param_1+0x10)!=0) FUN_000865fc(0x20005bb8,param_1);
  }
}

