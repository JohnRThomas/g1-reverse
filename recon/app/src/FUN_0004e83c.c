/* Reconstructed FUN_0004e83c @ 0x4e83c  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int FUN_0004e048(int,void*);
extern int FUN_0004e098(int,void*,void*);
extern int FUN_0004e3c0(void*);
extern int FUN_0004e3dc(void*);
extern int FUN_0007f344(void*);
int FUN_0004e83c(int param_1,int param_2,int param_3,unsigned int param_4){
  unsigned int args[4];
  int iVar1, iVar3; unsigned int uVar4,uVar5; unsigned int uVar2;
  args[0]=(unsigned int)param_1; args[1]=1; args[2]=(unsigned int)param_3; args[3]=param_4;
  iVar3=FUN_0004e048(9,args);
  if(iVar3==0){
    iVar3=FUN_0004e098(9,args+1,args+2);
    iVar1=0x2000a114UL;
    if(iVar3==0 || iVar3==-0xc){
      if(args[3]<0x10000){
        uVar5=0; uVar4=0;
        do{
          uVar4=uVar4+args[3];
          if(*(unsigned int*)(args[0]+8)<uVar4){ uVar5=uVar5&0xffff; break; }
          uVar5=uVar5+1;
        }while(uVar5!=8);
        *(volatile short*)(0x2000a114UL+0x14)=(short)args[3];
        *(volatile short*)(iVar1+0x16)=(short)uVar5;
        *(int*)(iVar1+8)=*(int*)(args[0]+4);
        *(int*)(iVar1+0x3c)=*(int*)(args[0]+0xc);
        iVar3=FUN_0007f344((void*)iVar1);
        uVar2=0x200027fcUL;
        if(iVar3==0){
          *(int*)(iVar1+4)=0x200027fcUL;
          FUN_0004e3c0((void*)iVar1);
          *(int*)(iVar1+4)=uVar2;
          FUN_0004e3dc((void*)iVar1);
        }
      } else { iVar3=-0x21; }
    }
  }
  return iVar3;
}
