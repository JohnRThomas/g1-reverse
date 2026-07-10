/* Reconstructed FUN_00018208 @ 0x18208  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void FUN_000864c2(unsigned);
extern void FUN_00086534(void*,int,int);
extern unsigned FUN_00076d6c(int);
extern void FUN_00086c78(unsigned,int,int,unsigned);
void FUN_00018208(uint32_t *param_1,unsigned param_2,unsigned param_3,unsigned param_4){
  uint32_t *puVar1; unsigned uVar2;
  param_1[0x93]=(uint32_t)(param_1+0xe5);
  *param_1=0x2201d;
  FUN_000864c2(0x20006a1c);
  param_1[3]=0x17e85;
  FUN_00086534(param_1+0x86,0,1);
  FUN_00086534(param_1+0x8c,0,2);
  param_1[0x94]=(uint32_t)(param_1+0x230);
  puVar1=(uint32_t*)0x20006a30;
  *(volatile uint8_t*)((int)param_1+0x365)=0;
  *(volatile uint8_t*)((int)param_1+0x366)=0;
  *(volatile uint8_t*)((int)(param_1+0xd9))=0;
  *(volatile uint32_t*)puVar1=(uint32_t)param_1;
  uVar2=FUN_00076d6c(0x15);
  param_1[0x95]=uVar2;
  FUN_00086c78(uVar2,0,0x15,param_4);
  return;
}

