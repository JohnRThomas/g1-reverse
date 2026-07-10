/* Reconstructed FUN_00019ac0 @ 0x19ac0  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_000167a8(void);
extern void FUN_000182c8(void);
extern void FUN_00018ab0(void);
extern void FUN_00072880(int);
int FUN_00019ac0(int param_1){
  int iVar1;
  FUN_00018ab0();
  if(param_1==0){
    iVar1=FUN_000167a8();
    if(*(volatile uint8_t*)(iVar1+0x1070)!=1) return 0;
    iVar1=FUN_000167a8();
    *(volatile uint8_t*)(iVar1+0x1070)=0;
  } else {
    if(*(volatile uint32_t*)0x20007518UL==0) return 0;
    FUN_000182c8();
    iVar1=FUN_000167a8();
    if(*(volatile uint8_t*)(iVar1+0x1070)!=0) return 0;
    iVar1=FUN_000167a8();
    *(volatile uint8_t*)(iVar1+0x1070)=1;
  }
  iVar1=FUN_000167a8();
  *(volatile uint32_t*)(iVar1+0x104c)=0;
  iVar1=FUN_000167a8();
  FUN_00072880(iVar1+0x80);
  return 0;
}

