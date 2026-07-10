/* Reconstructed FUN_0007d7b6 @ 0x7d7b6  (parity: 60/60 trials, PROVEN) */
#include <stdint.h>
extern int FUN_0007d4ec(void);
extern void FUN_00047698(unsigned int,unsigned int);
extern void FUN_000476a8(void);
void FUN_0007d7b6(int param_1,unsigned int param_2){
  int iVar1=FUN_0007d4ec();
  unsigned char local_24[8]; int iVar2;
  local_24[0]=0;
  iVar2=param_1+(int)((param_2/0xf000)*0xf000);
  for(; param_1!=iVar2; param_1=param_1+0xf000){
    FUN_00047698(0xffffffff,0xffffffff);
    (*(void(**)(int,int,unsigned int,void*,int))(*(int*)(iVar1+0x374)+8))(*(int*)(iVar1+0x374),param_1,0xf000,local_24,1);
    FUN_000476a8();
  }
  FUN_00047698(0xffffffff,0xffffffff);
  (*(void(**)(int,int,unsigned int,void*,int))(*(int*)(iVar1+0x374)+8))(*(int*)(iVar1+0x374),param_1,param_2%0xf000,local_24,1);
  FUN_000476a8();
}

