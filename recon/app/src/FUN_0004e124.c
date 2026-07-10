/* Reconstructed FUN_0004e124 @ 0x4e124  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void FUN_0004d944(unsigned int,unsigned int,void*,int);
extern int FUN_00083a92(unsigned int,unsigned int,void*);
int FUN_0004e124(int param_1,unsigned int param_2){
  int iVar1,iVar2; int local_24; int local_20=0;
  struct{unsigned int a,b; int c;} s;
  iVar1=FUN_00083a92(*(unsigned int*)(param_1+0xc),param_2,&local_24);
  if(iVar1==0){
    if(*(int*)(param_1+0x20)!=local_24){
      iVar2=(*(int(**)(unsigned int,int,int))(*(int*)(*(int*)(param_1+0xc)+8)+8))(*(unsigned int*)(param_1+0xc),local_24,local_20);
      if(iVar2==0) *(int*)(param_1+0x20)=local_24;
      else{ s.b=0x000f1036; s.a=3; s.c=iVar2; FUN_0004d944(0x000880d8,0x1840,&s,0); iVar1=iVar2; }
    }
  } else { s.b=0x000f1015; s.a=3; s.c=iVar1; FUN_0004d944(0x000880d8,0x1840,&s,0); }
  return iVar1;
}

