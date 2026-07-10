/* Reconstructed FUN_00052180 @ 0x52180  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_00080872(int,void*,int,void*);
extern int FUN_00052038(int,void*,int,int);
extern int FUN_000809f6(int);
extern int FUN_000516ac(int);
extern void FUN_00051fe4(void);
extern void FUN_0005160c(int,int,unsigned int);
int FUN_00052180(int param_1){
  int iVar1; unsigned int uVar2; int uVar3; int iVar4;
  int local_34; int uStack_30; char auStack_2c[8]; int local_24,local_20,local_1c; int* local_18; char local_14;
  local_24 = 0x000f272f;
  iVar4 = *(int*)(param_1+8);
  local_20 = 4;
  local_34 = 1;
  uStack_30 = 0;
  local_1c = 0x00085f8d;
  local_18 = &local_34;
  local_14 = 0;
  iVar1 = FUN_00080872(*(int*)(param_1+4)+4, &local_24, 1, &uStack_30);
  if(iVar1==0){
    iVar1 = FUN_00052038(local_34, auStack_2c, 0, 0);
    uVar3 = 0;
    if((iVar1==0) && (iVar1=FUN_000809f6(local_34), iVar1!=0)){
      uVar2 = 9;
    } else {
      uVar2 = FUN_000516ac(local_34);
      FUN_00051fe4();
      if(uVar2==0){ return 0; }
      uVar2 = uVar2 & 0xffff;
    }
    FUN_0005160c(iVar4+4, 1, uVar2);
  } else {
    uVar3 = 3;
  }
  (void)local_20; (void)local_1c; (void)local_18; (void)local_14;
  return uVar3;
}

