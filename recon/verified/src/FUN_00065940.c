/* Reconstructed FUN_00065940 @ 0x65940  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;
extern void FUN_000500ac(int);
extern int FUN_000655ec(uint32_t);
extern void FUN_00086c78(uint32_t,int,int);
uint32_t FUN_00065940(void){
  int iVar1=0x20002bc0;
  uint32_t uVar3=0x0bad0005;
  int iVar2=0;
  if(*(volatile uint8_t*)(0x20002bc0UL+0x78)==0){
    FUN_00086c78(0x20002bc0UL+0x10,0,0x60);
    uint uVar4=0;
    do{
      iVar2=FUN_000655ec(uVar4&0xff);
      if((iVar2-0x100U)>>2==0x1f){
        *(volatile uint32_t*)(iVar2+0x5000d000UL)=0;
      }
      iVar2=0x5000d000;
      uVar4=uVar4+1;
    }while(uVar4!=8);
    *(volatile uint32_t*)(0x5000d000UL+0x17c)=0;
    FUN_000500ac(0xd);
    *(volatile uint32_t*)(iVar2+0x304)=0x80000000;
    uVar3=0x0bad0000;
    *(volatile uint8_t*)(iVar1+0x78)=1;
    *(volatile uint32_t*)(iVar1+0x74)=1;
  }
  return uVar3;
}

