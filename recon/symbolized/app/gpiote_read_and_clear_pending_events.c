#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00065620 @ 0x00065620
 * public-name: gpiote_read_and_clear_pending_events
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gpiote_in_event_reg_offset               <= FUN_000655ec @ 0x000655ec
 *   gpiote_read_and_clear_pending_events     <= FUN_00065620 @ 0x00065620
 */
/* Reconstructed FUN_00065620 @ 0x65620  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "../../headers/g1_nrf_regs.h"
extern int gpiote_in_event_reg_offset(unsigned int);
unsigned int gpiote_read_and_clear_pending_events(unsigned int param_1){
  unsigned int uVar3=0,uVar4=0,uVar2;
  int iVar1;
  do{
    iVar1=gpiote_in_event_reg_offset(uVar3&0xff);
    uVar2=1u<<((((unsigned int)(iVar1-0x100))>>2)&0xff);
    if((param_1&uVar2)!=0){
      if(*(volatile int*)(iVar1+G1_NRF_GPIOTE0_S_BASE)!=0){
        *(volatile int*)(iVar1+G1_NRF_GPIOTE0_S_BASE)=0;
        (void)*(volatile int*)(iVar1+G1_NRF_GPIOTE0_S_BASE);
        uVar4|=uVar2;
      }
    }
    uVar3++;
  }while(uVar3!=8);
  if(*(volatile int*)(G1_NRF_GPIOTE0_S_BASE+0x17c)!=0){
    *(volatile int*)(G1_NRF_GPIOTE0_S_BASE+0x17c)=0;
    (void)*(volatile int*)(G1_NRF_GPIOTE0_S_BASE+0x17c);
    uVar4|=0x80000000u;
  }
  return uVar4;
}
