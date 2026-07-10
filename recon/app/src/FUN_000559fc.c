/* Reconstructed FUN_000559fc @ 0x559fc  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;
extern void FUN_00081320(uint32_t);
extern void FUN_00081180(uint32_t,uint32_t);
extern int FUN_0008117a(uint32_t);
extern int FUN_00055698(uint32_t);
extern int FUN_00056f08(uint32_t,uint32_t,uint32_t);
extern void FUN_00056704(void);
extern void FUN_000566a4(int);
extern uint FUN_000812d2(uint32_t,int);
uint FUN_000559fc(void){
  int iVar1; uint uVar2; uint32_t uVar3;
  FUN_00081320(0x20002018);
  FUN_00081180(0x20002028,0xffffbfff);
  iVar1=FUN_0008117a(0x20002028);
  if(iVar1<<0x18 < 0){
    iVar1=FUN_0008117a(0x20002028);
    if(iVar1<<0x15 < 0){
      iVar1=FUN_00055698(0x20002018);
      if(iVar1==0){ uVar3=4; iVar1=0xf2b33; }
      else { uVar3=5; iVar1=0x20002021; }
      iVar1=FUN_00056f08(*(volatile uint8_t*)0x20002018UL,iVar1,uVar3);
      if(iVar1!=0){
        *(volatile uint8_t*)(iVar1+0xc)=0;
        FUN_00056704();
        FUN_000566a4(iVar1);
      }
    }
    uVar2=FUN_000812d2(0x20002018,0);
    return uVar2;
  }
  return (uint)(iVar1<<0x18)>>0x1f;
}

