/* named: Balloc */
/* Reconstructed Balloc @ 0x785d4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void* malloc(int);
extern void* libc_fatal_error_and_abort(unsigned int,int,int,unsigned int);
extern void* heap_calloc(int,int,int);
unsigned int* Balloc(int param_1,unsigned int param_2){
  unsigned int* puVar1; void* uVar2; int iVar3,iVar4;
  if(*(int*)(param_1+0x24)==0){
    puVar1=(unsigned int*)malloc(0x10);
    *(unsigned int**)(param_1+0x24)=puVar1;
    if(puVar1==0) puVar1=(unsigned int*)libc_fatal_error_and_abort(0x000f8cd5,0x66,0,0x000f8bb7);
    puVar1[1]=0; puVar1[2]=0; *puVar1=0; puVar1[3]=0;
  }
  iVar4=*(int*)(param_1+0x24);
  if(*(int*)(iVar4+0xc)==0){
    uVar2=heap_calloc(param_1,4,0x21);
    iVar3=*(int*)(param_1+0x24);
    *(void**)(iVar4+0xc)=uVar2;
    if(*(int*)(iVar3+0xc)!=0) goto L602;
    L638: puVar1=0;
  } else {
    L602:
    iVar4=*(int*)(*(int*)(param_1+0x24)+0xc);
    puVar1=*(unsigned int**)(iVar4+param_2*4);
    if(puVar1==0){
      iVar4=1<<(param_2&0xff);
      puVar1=(unsigned int*)heap_calloc(param_1,1,(iVar4+5)*4);
      if(puVar1==0) goto L638;
      puVar1[1]=param_2; puVar1[2]=iVar4;
    } else {
      *(unsigned int*)(iVar4+param_2*4)=*puVar1;
    }
    puVar1[3]=0; puVar1[4]=0;
  }
  return puVar1;
}

