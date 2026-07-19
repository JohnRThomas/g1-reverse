#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0004d2d0 @ 0x0004d2d0
 * public-name: activate_foreach_backend
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   activate_foreach_backend                 <= FUN_0004d2d0 @ 0x0004d2d0
 * address symbols (name @ address):
 *   rodata_882a0                             @ 0x000882a0
 */
/* Reconstructed activate_foreach_backend @ 0x0004d2d0 from log_core.c.
 * Signature ownership score 0.971; raw backmap FUN_0004d2d0@0x0004d2d0. */

#include <stdint.h>
#define activate_foreach_backend activate_foreach_backend
typedef int (*backend_ready_fn)(const void *backend);
extern void log_msg_commit(const void *backend,void *context,uint32_t level); /* log_backend_enable */
uint32_t activate_foreach_backend(uint32_t mask)
{
 uint32_t pending=mask; volatile uint8_t *table=(volatile uint8_t*)((unsigned long)&rodata_882a0) /*=0x882a0*/;
 while(pending!=0u){
  uint32_t index=(uint32_t)__builtin_ctz(pending);uint32_t bit=1u<<index;
  volatile uint8_t *backend=table+index*16u;pending&=~bit;
  if(backend[0x0cu]!=0u){
   const volatile uintptr_t *api_slot=(const volatile uintptr_t*)backend;
   backend_ready_fn ready=*(backend_ready_fn *)(uintptr_t)(*api_slot+0x10u);
   if(ready==0 || ready((const void*)backend)==0){
    mask&=~bit;void *context=**(void***)(backend+4u);log_msg_commit((const void*)backend,context,4u);
   }
  }
 }
 return mask;
}
