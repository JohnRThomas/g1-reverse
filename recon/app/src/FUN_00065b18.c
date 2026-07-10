/* Reconstructed FUN_00065b18 @ 0x65b18  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_00065434(int);
extern int FUN_00065448(void);
extern int FUN_00065460(int);
extern int FUN_000654ac(int);
extern void FUN_00065504(int);
extern int FUN_00065584(int*);
extern void FUN_00065acc(int);
uint32_t FUN_00065b18(int param_1,int param_2){
  int local_c=param_2;
  int iVar2=FUN_00065448();
  uint32_t uVar3=0x0bad0004;
  if(iVar2!=0){
    FUN_00065acc(param_1);
    iVar2=FUN_00065460(param_1);
    if(iVar2!=0){
      short sVar1=(short)FUN_000654ac(param_1);
      *(volatile uint32_t*)(sVar1*4+0x5000d510UL)=0;
      *(volatile uint32_t*)(sVar1*4+0x5000d510UL)=0;
    }
    FUN_00065504(param_1);
    iVar2=FUN_00065434(param_1);
    *(volatile uint16_t*)(0x20002bc0UL+(iVar2+8)*2)=0;
    local_c=param_1;
    iVar2=FUN_00065584(&local_c);
    iVar2=iVar2+local_c*4;
    *(volatile uint32_t*)(iVar2+0x200)=(0xfffcf0f0 & *(volatile uint32_t*)(iVar2+0x200))|2;
    uVar3=0x0bad0000;
  }
  return uVar3;
}

