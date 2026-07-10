/* Reconstructed FUN_0003439c @ 0x3439c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;
extern int FUN_000167a8(void);
extern void FUN_00033b0c(void);
extern int FUN_00033cf8(void);
extern int FUN_0007d224(void);
void FUN_0003439c(void){
  int iVar6=0x20007dac;
  volatile uint8_t* pbVar2=(volatile uint8_t*)0x2001a22aUL;
  if( *(volatile int*)(0x20007dacUL + (uint)*pbVar2 * 0x1b4) != 0 &&
      *(volatile int8_t*)(0x20007dacUL + (uint)*pbVar2 * 0x1b4 + 0xf) == 0 ){
    int iVar4=FUN_000167a8();
    uint8_t uVar3=(uint8_t)FUN_00033cf8();
    *(volatile uint8_t*)(iVar4+0xdd)=uVar3;
    iVar4=FUN_000167a8();
    uint uVar7=*(volatile uint8_t*)(iVar4+0xdd);
    if(uVar7!=0){
      iVar4=FUN_000167a8();
      uVar7=(*(volatile uint8_t*)(iVar4+0xdd)-1)&0xff;
    }
    *pbVar2=(uint8_t)uVar7;
    uint32_t uVar5=FUN_0007d224();
    uint8_t bVar1=*pbVar2;
    *(volatile uint32_t*)(uVar7*0x1b4 + iVar6 + 4)=uVar5;
    *(volatile uint8_t*)((uint)bVar1*0x1b4 + iVar6 + 0xf)=1;
    int iVar6b=FUN_000167a8();
    uVar3=(uint8_t)FUN_00033cf8();
    *(volatile uint8_t*)(iVar6b+0xdd)=uVar3;
  }
  FUN_00033b0c();
}

