/* readable reconstruction; identity: FUN_00086596 @ 0x00086596
 * public-name: cancel_async_locked
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   cancel_async_locked                      <= FUN_00086596 @ 0x00086596
 */
/* Reconstructed cancel_async_locked @ 0x00086596 from Zephyr work.c.
 * Raw backmap: FUN_00086596@0x00086596. */

#include <stdint.h>
#define cancel_async_locked cancel_async_locked
extern uint32_t flag_test_and_clear(volatile uint32_t *flags,uint32_t bit);
int cancel_async_locked(void *work_arg)
{
 uint8_t *work=(uint8_t*)work_arg;
 volatile uint32_t *flags=(volatile uint32_t*)(work+0x0cu);
 uint32_t initial=*flags;
 if((initial&2u)==0u){
  uint8_t *queue=*(uint8_t**)(work+8u);
  if(flag_test_and_clear(flags,2u)!=0u){
   uint8_t *node=*(uint8_t**)(queue+0xd8u); uint8_t *previous=0;
   while(node!=0){
    if(node==work){
     uint8_t *next=*(uint8_t**)work;
     if(previous==0){*(uint8_t**)(queue+0xd8u)=next;if(*(uint8_t**)(queue+0xdcu)==work)*(uint8_t**)(queue+0xdcu)=next;}
     else{*(uint8_t**)previous=next;if(*(uint8_t**)(queue+0xdcu)==work)*(uint8_t**)(queue+0xdcu)=previous;}
     *(uint8_t**)work=0;break;
    }
    previous=node;node=*(uint8_t**)node;
   }
  }
 }
 uint32_t busy=*flags&0xfu;
 if(busy!=0u){*flags|=2u;busy|=2u;}
 return (int)busy;
}
