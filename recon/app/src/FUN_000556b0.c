/* Reconstructed FUN_000556b0 @ 0x556b0  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_00055698(unsigned long);
extern int FUN_00056704(int,unsigned int);
extern int FUN_00056e34(unsigned int,unsigned int);
extern int FUN_00056ea8(unsigned int,void*);
unsigned int FUN_000556b0(unsigned char* param_1,int* param_2){
  unsigned char uVar1=*param_1;
  int iVar2; unsigned int uVar3;
  *(volatile unsigned char*)(0x20002000+0x6f)=uVar1;
  iVar2=FUN_00055698(param_1);
  if(iVar2==0){
    iVar2=FUN_00056e34(uVar1,0x000f2b33);
    if(iVar2!=0){ uVar3=4; FUN_00056704(iVar2,uVar3); *param_2=iVar2; return 0; }
  } else {
    iVar2=FUN_00056ea8(uVar1,param_1+9);
    if(iVar2!=0) return 0xffffffea;
    iVar2=FUN_00056e34(*param_1,(unsigned int)(param_1+9));
    if(iVar2!=0){ uVar3=5; FUN_00056704(iVar2,uVar3); *param_2=iVar2; return 0; }
  }
  return 0xfffffff4;
}

