#include "g1_app_symbols.h"
/* named: msg_content_recalc_unread */
/* globals referenced:
//   0x20007dac  g_message_pool               
//   0x2001a22a  g_message_pool_index         
*/
/* Reconstructed msg_content_recalc_unread @ 0x33cf8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
uint32_t msg_content_recalc_unread(void){
  uint32_t counter = 0, uVar4 = 0, uVar5 = 0, bVar1 = 0;
  uint32_t iVar6 = (g_message_pool) /*=0x20007dac*/;
  volatile uint8_t *DAT = (volatile uint8_t*)((uintptr_t)&g_message_pool_index) /*=0x2001a22a*/;
  uint32_t r0;
  while(1){
    r0 = counter & 0xff;
    if(*(volatile uint8_t*)(iVar6 + 0x10) == 0){
      if(bVar1) *DAT = (uint8_t)uVar4;
      if(uVar5 != 0) return (r0 - uVar5) & 0xff;
      if(r0 != 0){ uVar5 = 0; *DAT = 0; }
      else { *DAT = 0xff; }
      return (r0 - uVar5) & 0xff;
    }
    if(*(volatile uint8_t*)(iVar6 + 0xf) != 0){
      uVar4 = r0;
      bVar1 = 1;
      uVar5 = (uVar5 + 1) & 0xff;
    }
    counter++;
    iVar6 += 0x1b4;
    if(counter == 10) break;
  }
  if(bVar1) *DAT = (uint8_t)uVar4;
  r0 = 10;
  if(uVar5 != 0) return (r0 - uVar5) & 0xff;
  uVar5 = 0; *DAT = 0;
  return (r0 - uVar5) & 0xff;
}

