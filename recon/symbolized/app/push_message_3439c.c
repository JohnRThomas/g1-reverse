#include "g1_app_symbols.h"
/* named: push_message_3439c */
/* globals referenced:
//   0x20007dac  g_message_pool               
//   0x2001a22a  g_message_pool_index         
*/
/* Reconstructed push_message_3439c @ 0x3439c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;
extern int get_device_info(void);
extern void msg_queue_debug_dump(void);
extern int msg_content_recalc_unread(void);
extern int get_timestamp(void);
void push_message_3439c(void){
  int iVar6=(g_message_pool) /*=0x20007dac*/;
  volatile uint8_t* pbVar2=(volatile uint8_t*)((uintptr_t)&g_message_pool_index) /*=0x2001a22a*/;
  if( *(volatile int*)((g_message_pool) /*=0x20007dac*/ + (uint)*pbVar2 * 0x1b4) != 0 &&
      *(volatile int8_t*)((g_message_pool) /*=0x20007dac*/ + (uint)*pbVar2 * 0x1b4 + 0xf) == 0 ){
    int iVar4=get_device_info();
    uint8_t uVar3=(uint8_t)msg_content_recalc_unread();
    *(volatile uint8_t*)(iVar4+0xdd)=uVar3;
    iVar4=get_device_info();
    uint uVar7=*(volatile uint8_t*)(iVar4+0xdd);
    if(uVar7!=0){
      iVar4=get_device_info();
      uVar7=(*(volatile uint8_t*)(iVar4+0xdd)-1)&0xff;
    }
    *pbVar2=(uint8_t)uVar7;
    uint32_t uVar5=get_timestamp();
    uint8_t bVar1=*pbVar2;
    *(volatile uint32_t*)(uVar7*0x1b4 + iVar6 + 4)=uVar5;
    *(volatile uint8_t*)((uint)bVar1*0x1b4 + iVar6 + 0xf)=1;
    int iVar6b=get_device_info();
    uVar3=(uint8_t)msg_content_recalc_unread();
    *(volatile uint8_t*)(iVar6b+0xdd)=uVar3;
  }
  msg_queue_debug_dump();
}

