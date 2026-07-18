/* readable reconstruction; identity: FUN_000820ae @ 0x000820ae
 * public-name: att_req_send_process
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   att_req_send_process                     <= FUN_000820ae @ 0x000820ae
 */
/* Reconstructed att_req_send_process @ 0x000820ae from NCS 2.5.1 att.c.
 * Raw backmap: FUN_000820ae@0x000820ae. */

#include <stdint.h>
#define att_req_send_process att_req_send_process
extern void *sys_slist_get(void *list);
extern int FUN_00058b78(void *channel,void *request); /* bt_att_chan_req_send */
void att_req_send_process(void *att_arg)
{
 uint8_t *att=(uint8_t*)att_arg;
 uintptr_t node=*(volatile uintptr_t*)(att+0x30u);
 if(node==0u)return;
 uint8_t *channel=(uint8_t*)(node-0x190u);
 uintptr_t next=*(volatile uintptr_t*)node;
 uint8_t *next_channel=next?(uint8_t*)(next-0x190u):0;
 void *request=0; uint8_t *previous=0;
 for(;;){
  if(*(volatile uintptr_t*)(channel+0x124u)==0u){
   if(request!=0 || previous==0){
    request=sys_slist_get(att+4u); previous=channel;
    if(request!=0){
     if(FUN_00058b78(channel,request)>=0)return;
     *(uintptr_t*)request=*(volatile uintptr_t*)(att+4u);
     *(volatile uintptr_t*)(att+4u)=(uintptr_t)request;
     if(*(volatile uintptr_t*)(att+8u)==0u)*(volatile uintptr_t*)(att+8u)=(uintptr_t)request;
    }
   }
  }
  if(next_channel==0)return;
  channel=next_channel;
  next=*(volatile uintptr_t*)(next_channel+0x190u);
  next_channel=next?(uint8_t*)(next-0x190u):0;
 }
}
