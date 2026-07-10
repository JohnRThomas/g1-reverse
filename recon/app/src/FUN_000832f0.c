/* Reconstructed FUN_000832f0 @ 0x832f0  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int FUN_0005cb38(int,...);
extern int FUN_0005f24c(int,...);
extern int FUN_0005f5d0(int,...);
extern int FUN_00082ff6(int,...);
extern int FUN_0008304c(int,...);
extern int FUN_00083090(int,...);
extern int FUN_000830b0(int,...);
extern int FUN_0008323a(int,...);
unsigned FUN_000832f0(int param_1){
  int iVar4 = param_1+4;
  int iVar1 = FUN_00082ff6(iVar4,10);
  unsigned uVar2;
  if(iVar1==0){
    uVar2 = FUN_00083090(param_1,4);
    int iVar3 = *(volatile int*)(param_1+0xf0);
    iVar1 = FUN_000830b0(uVar2,3);
    if(iVar1!=0){
      uVar2 = FUN_0005f5d0(iVar1+0xc,0x10);
      iVar3 = FUN_0008323a(param_1+0x47,param_1+0x27,param_1+9,param_1+0x10,iVar3+0x97,iVar3+0x9e,uVar2);
      if(iVar3==0){
        FUN_0005cb38(param_1,iVar1,0);
        FUN_0008304c(iVar4,0);
        return 0;
      }
      FUN_0005f24c(iVar1);
    }
    uVar2 = 8;
  } else {
    FUN_00083090(iVar4,0);
    uVar2 = 0;
  }
  return uVar2;
}

