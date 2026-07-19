#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_bt_uuid_32__param_0185                 [param_0185; library]
 *   param_2          => struct g1_layout_bt_uuid_128__param_0186                [param_0186; library]
 * Raw function identity: 0x000531e4.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_000531e4 @ 0x000531e4
 * public-name: bt_uuid_expand_to_128
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_uuid_expand_to_128                    <= FUN_000531e4 @ 0x000531e4
 * address symbols (name @ address):
 *   rodata_f2cc8                             @ 0x000f2cc8
 */
/* Reconstructed FUN_000531e4 @ 0x531e4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
void bt_uuid_expand_to_128(char *param_1,char *param_2){
  char cVar1=*(volatile char*)param_1;
  if(cVar1==1){
    volatile uint32_t* s=(volatile uint32_t*)((unsigned long)&rodata_f2cc8) /*=0xf2cc8*/;
    volatile uint32_t* d=(volatile uint32_t*)param_2;
    volatile uint32_t* end=(volatile uint32_t*)(((unsigned long)&rodata_f2cc8) /*=0xf2cc8*/+0x10);
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
    volatile uint32_t* s=(volatile uint32_t*)((unsigned long)&rodata_f2cc8) /*=0xf2cc8*/;
    volatile uint32_t* d=(volatile uint32_t*)param_2;
    volatile uint32_t* end=(volatile uint32_t*)(((unsigned long)&rodata_f2cc8) /*=0xf2cc8*/+0x10);
    do{ *d=*s; d++; s++; }while(s!=end);
    *(volatile uint8_t*)d=*(volatile uint8_t*)s;
    uint16_t uVar2=*(volatile uint16_t*)(param_1+2);
    *(volatile uint8_t*)(param_2+0xd)=(uint8_t)uVar2;
    *(volatile uint8_t*)(param_2+0xe)=(uint8_t)(uVar2>>8);
  }
}
