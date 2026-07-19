#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_uarte_driver_ctx__param_0314           [param_0314; G1-original]
 * Raw function identity: 0x0008496c.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0008496c @ 0x0008496c
 * public-name: audio_dma_start_transfer
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   audio_hw_lock_get_status_byte            <= FUN_0007ef1c @ 0x0007ef1c
 *   audio_dma_start_transfer                 <= FUN_0008496c @ 0x0008496c
 */
/* Reconstructed FUN_0008496c @ 0x8496c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void audio_hw_lock_get_status_byte(int,void*,uint32_t,uint32_t,int);
void audio_dma_start_transfer(int param_1,uint32_t param_2,uint32_t param_3,uint32_t param_4){
  volatile int* piVar3=*(volatile int* volatile*)(param_1+4);
  int iVar2=*(volatile int*)piVar3;
  volatile uint32_t uStack_1c=param_2;
  audio_hw_lock_get_status_byte(param_1,(void*)((int)&uStack_1c+3),param_3,param_4,param_1);
  if(((volatile uint8_t*)&uStack_1c)[3]==0){
    *(volatile uint32_t*)(iVar2+0x544)=param_2;
    *(volatile uint32_t*)(iVar2+0x548)=param_3;
    *(volatile uint32_t*)(iVar2+0x120)=0;
    *(volatile uint32_t*)(iVar2+0x158)=0;
    if((*(volatile int*)((int)piVar3+4)<<0x1b)<0){
      int iVar1=*(volatile int*)(*(volatile int*)(param_1+0x10)+0xc);
      if(iVar1!=0) *(volatile uint32_t*)(iVar1+0xc0)=*(volatile uint32_t*)(iVar1+0xc0)|1;
      *(volatile uint32_t*)(*(volatile int*)(*(volatile int*)(param_1+4))+0x500)=8;
      *(volatile uint32_t*)(iVar2+0x304)=0x400000;
    }
    *(volatile uint32_t*)(iVar2+8)=1;
  }
}
