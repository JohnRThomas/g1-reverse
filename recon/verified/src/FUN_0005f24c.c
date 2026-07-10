/* Reconstructed FUN_0005f24c @ 0x5f24c  (parity: 60/60 trials, PROVEN) */
#include <stdint.h>
extern void FUN_0007e2fa(unsigned int,...);
extern void FUN_0007e2ec(unsigned int,...);
extern void FUN_00086518(int,int);
void FUN_0005f24c(int param_1){
  int iVar1=0x20003a7c; char cVar2; int iVar4; void* pcVar3;
  if(param_1==0){
    FUN_0007e2fa(0x00099cbd,0x000f45be,0x000f539a,0x1d3);
    FUN_0007e2ec(0x000f539a,0x1d3);
  }
  do{
    iVar4=*(int*)(param_1+4);
    cVar2=*(char*)(param_1+8)-1;
    *(char*)(param_1+8)=cVar2;
    if(cVar2!=0) return;
    if(*(int*)(param_1+0x14)!=0){
      if(((int)((unsigned int)*(unsigned char*)(param_1+9)<<0x1f))>=0){
        (**(void(***)(int))((unsigned int)*(unsigned char*)(param_1+10)*0x34+iVar1+0x2c))(param_1);
      }
      *(int*)(param_1+0x14)=0;
    }
    *(int*)(param_1+0xc)=0;
    *(int*)(param_1+4)=0;
    pcVar3=*(void**)((unsigned int)*(unsigned char*)(param_1+10)*0x34+iVar1+0x28);
    if(pcVar3==0) FUN_00086518((int)((unsigned int)*(unsigned char*)(param_1+10)*0x34+iVar1),param_1);
    else ((void(*)(int))pcVar3)(param_1);
    param_1=iVar4;
  }while(iVar4!=0);
}

