/* readable reconstruction; identity: FUN_00033cf8 @ 0x00033cf8
 * public-name: msg_content_recalc_unread
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   msg_content_recalc_unread                <= FUN_00033cf8 @ 0x00033cf8
 * address symbols (name @ address):
 *   g_message_pool                           @ 0x20007dac
 *   g_message_pool_index                     @ 0x2001a22a
 */
/* Reconstructed FUN_00033cf8 @ 0x33cf8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
uint32_t msg_content_recalc_unread(void){
  uint32_t counter = 0, uVar4 = 0, uVar5 = 0, bVar1 = 0;
  uint32_t iVar6 = 0x20007dacUL;
  volatile uint8_t *DAT = (volatile uint8_t*)0x2001a22aUL;
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
