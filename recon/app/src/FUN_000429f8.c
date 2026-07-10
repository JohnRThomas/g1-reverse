/* Reconstructed FUN_000429f8 @ 0x429f8  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int FUN_000167a8(void);
void FUN_000429f8(void){
  int iVar1;
  iVar1=FUN_000167a8();
  if(((((*(char*)(*(int*)(iVar1+0x1014)+2)==5) ||
       (iVar1=FUN_000167a8(), *(char*)(*(int*)(iVar1+0x1014)+2)==0x13)) ||
      (iVar1=FUN_000167a8(), *(char*)(*(int*)(iVar1+0x1014)+2)==0x14)) ||
     (iVar1=FUN_000167a8(), *(char*)(*(int*)(iVar1+0x1014)+2)==0x15)) &&
    ((*(volatile char*)0x2001cdceUL==2) &&
     (iVar1=FUN_000167a8(), *(char*)(*(int*)(iVar1+0x1014)+3)==1))){
    *(volatile char*)0x2001cdd1UL=1;
  }
  return;
}

