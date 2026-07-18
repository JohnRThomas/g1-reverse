/* Reconstructed cancel_async_locked @ 0x00086596 from Zephyr work.c.
 * Raw backmap: FUN_00086596@0x00086596. */

#include <stdint.h>
#ifdef G1_APP_SDK_INLINE_COHESION
/* Exact Zephyr 3.4.99 work.c local owner; raw FUN_00086554 @ 0x00086554. */
static __attribute__((always_inline)) inline uint32_t
flag_test_and_clear(volatile uint32_t *flags, uint32_t bit)
{
 uint32_t old = *flags;
 *flags = old & ~(1u << (bit & 0xffu));
 return (old >> (bit & 0xffu)) & 1u;
}
#else
extern uint32_t flag_test_and_clear(volatile uint32_t *flags,uint32_t bit);
#endif
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
