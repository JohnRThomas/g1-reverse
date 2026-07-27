/* Reconstructed FUN_0003678c @ 0x3678c  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void DEBUG_PRINT(unsigned long, ...);
extern int FUN_00076d6c(int,...);
extern int FUN_00086c78(int,...);
void FUN_0003678c(int param_1,int param_2,unsigned param_3,unsigned param_4){
  volatile int *piVar1 = (volatile int*)0x20009fccUL;
  if(*piVar1==0){
    int iVar4 = FUN_00076d6c(0x140);
    *piVar1 = iVar4;
    if(iVar4==0){ DEBUG_PRINT(0xa8d69,0xa8e18,0xa7,param_4); return; }
    FUN_00086c78(iVar4,0,0x140);
  }
  volatile int *piVar3 = (volatile int*)0x20009fc8UL;
  volatile int *piVar2 = (volatile int*)0x20009fc4UL;
  unsigned uVar5 = 0;
  do{
    int iVar4 = *piVar2;
    if(param_2 <= iVar4) return;
    *piVar2 = iVar4 + 2;
    unsigned uVar7 = ((unsigned)param_1 << (uVar5 & 0xff)) & 0xc0;
    unsigned char uVar6;
    if(uVar7==0xc0) uVar6=0;
    else if(uVar7==0x80) uVar6=0xf;
    else if(uVar7==0x40) uVar6=0xf0;
    else if(uVar7==0) uVar6=0xff;
    else uVar6=0x99;
    *(volatile uint8_t*)((unsigned)*piVar1 + (unsigned)*piVar3) = uVar6;
    uVar5 += 2;
    *piVar3 = *piVar3 + 1;
  } while(uVar5!=8);
}

