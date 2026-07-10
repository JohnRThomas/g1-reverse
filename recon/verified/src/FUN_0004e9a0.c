/* Reconstructed FUN_0004e9a0 @ 0x4e9a0  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_0004e8e8(int);
extern int FUN_0004e98c(int);
extern void FUN_0007f406(unsigned int,unsigned int,void*);
extern void FUN_00086c04(int,unsigned int,int);
int FUN_0004e9a0(unsigned int* param_1,int param_2){
  int iVar2=0x2000a154; int iVar3,iVar4,iVar5,iVar6; short uVar1;
  struct{unsigned int a,b;} s;
  s.b=0x000f1237;
  if(*(volatile unsigned int*)(iVar2+0x134)<0x23){
    iVar3=FUN_0004e98c(*(unsigned char*)(*param_1));
    iVar4=FUN_0004e8e8(iVar3+param_2);
    s.b=0x000f1253;
    if(iVar4!=0){
      iVar5=*(volatile int*)(iVar2+0x134);
      *(volatile int*)(iVar2+0x134)=iVar5+1;
      iVar5=(iVar5+3)*8; iVar6=iVar2+iVar5;
      *(volatile short*)(iVar6+8)=*(short*)((char*)param_1+0x10);
      uVar1=*(short*)((char*)param_1+0x12);
      *(volatile int*)(iVar6+4)=iVar4+param_2;
      *(volatile char*)(iVar6+10)=(char)uVar1;
      FUN_00086c04(iVar4+param_2,*param_1,iVar3);
      return iVar5+4+iVar2;
    }
  }
  s.a=2;
  FUN_0007f406(0x00088130,0x1040,&s);
  return 0;
}

