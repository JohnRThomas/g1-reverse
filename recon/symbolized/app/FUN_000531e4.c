#include "g1_app_symbols.h"
/* named: FUN_000531e4 */
/* Reconstructed FUN_000531e4 @ 0x531e4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
void FUN_000531e4(char *param_1,char *param_2){
  char cVar1=*(volatile char*)param_1;
  if(cVar1==1){
    volatile uint32_t* s=(volatile uint32_t*)((uintptr_t)&rodata_f2cc8) /*=0xf2cc8*/;
    volatile uint32_t* d=(volatile uint32_t*)param_2;
    volatile uint32_t* end=(volatile uint32_t*)(((uintptr_t)&rodata_f2cc8) /*=0xf2cc8*/+0x10);
    do{ *d=*s; d++; s++; }while(s!=end);
    *(volatile uint8_t*)d=*(volatile uint8_t*)s;
    uint32_t uVar7=*(volatile uint32_t*)(param_1+4);
    *(volatile uint8_t*)(param_2+0xd)=(uint8_t)uVar7;
    *(volatile uint8_t*)(param_2+0xf)=(uint8_t)(uVar7>>0x10);
    *(volatile uint8_t*)(param_2+0xe)=(uint8_t)(uVar7>>8);
    *(volatile uint8_t*)(param_2+0x10)=(uint8_t)(uVar7>>0x18);
  } else if(cVar1==2){
    volatile uint32_t* s=(volatile uint32_t*)param_1;
    volatile uint32_t* d=(volatile uint32_t*)param_2;
    volatile uint32_t* end=(volatile uint32_t*)(param_1+0x10);
    do{ *d=*s; d++; s++; }while(s!=end);
    *(volatile uint8_t*)d=*(volatile uint8_t*)s;
  } else if(cVar1==0){
    volatile uint32_t* s=(volatile uint32_t*)((uintptr_t)&rodata_f2cc8) /*=0xf2cc8*/;
    volatile uint32_t* d=(volatile uint32_t*)param_2;
    volatile uint32_t* end=(volatile uint32_t*)(((uintptr_t)&rodata_f2cc8) /*=0xf2cc8*/+0x10);
    do{ *d=*s; d++; s++; }while(s!=end);
    *(volatile uint8_t*)d=*(volatile uint8_t*)s;
    uint16_t uVar2=*(volatile uint16_t*)(param_1+2);
    *(volatile uint8_t*)(param_2+0xd)=(uint8_t)uVar2;
    *(volatile uint8_t*)(param_2+0xe)=(uint8_t)(uVar2>>8);
  }
}

