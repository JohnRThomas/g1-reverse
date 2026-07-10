/* Reconstructed FUN_0005aba8 @ 0x5aba8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_0008016a(void*,void*,void*);
extern void FUN_00080294(void); /*unused decl replaced*/
extern int FUN_00080294_i(uint32_t,void*);
extern void FUN_000826e0(uint32_t);
extern void FUN_00082a42(uint32_t,int,void*);
extern void FUN_00082c9c(int,int,uint32_t,void*);
void FUN_0005aba8(void){
  volatile uint32_t local_140,uStack_13c,local_138,uStack_134,local_120;
  uint8_t auStack_118[96], auStack_b8[176];
  local_140=0;uStack_13c=0;local_138=0;uStack_134=0;
  int iVar2=FUN_0008016a(auStack_118,(void*)&local_140,auStack_b8);
  if(iVar2!=0){
    FUN_00082c9c(1,0xffff,0x8260d,auStack_118);
    iVar2=FUN_00080294_i(0x20006380,auStack_118);
    if(iVar2!=0){
      volatile uint8_t* puVar3=(volatile uint8_t*)(0x20006380UL+0x10);
      volatile uint8_t* puVar4=(volatile uint8_t*)0x20006380UL;
      int i=0;
      do{
        uint8_t uVar1=*puVar4;
        puVar3=puVar3-1;
        i=i+1;
        *puVar4=*puVar3;
        *puVar3=uVar1;
        puVar4=puVar4+1;
      }while(i!=8);
      FUN_000826e0(0x20006448);
      return;
    }
  }
  local_120=2;
  FUN_00082a42(0x88128,0x1040,(void*)&local_120);
}

