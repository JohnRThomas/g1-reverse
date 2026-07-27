/* readable reconstruction; identity: FUN_00065940 @ 0x00065940
 * public-name: g1_recon_nrfx_gpiote_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   arch_irq_enable                          <= FUN_000500ac @ 0x000500ac
 *   gpiote_in_event_reg_offset               <= FUN_000655ec @ 0x000655ec
 *   g1_recon_nrfx_gpiote_init                <= FUN_00065940 @ 0x00065940
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   g_gpiote_cb                              @ 0x20002bc0
 */
/* Reconstructed FUN_00065940 @ 0x65940  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "../headers/g1_nrf_regs.h"
typedef unsigned int uint;
extern int arch_irq_enable(int);
extern int gpiote_in_event_reg_offset(uint32_t);
extern void memset_bytes(void*, int, int);
uint32_t g1_recon_nrfx_gpiote_init(void){
  int iVar1=0x20002bc0;
  uint32_t uVar3=0x0bad0005;
  int iVar2=0;
  if(*(volatile uint8_t*)(0x20002bc0UL+0x78)==0){
    memset_bytes(0x20002bc0UL+0x10,0,0x60);
    uint uVar4=0;
    do{
      iVar2=gpiote_in_event_reg_offset(uVar4&0xff);
      if((iVar2-0x100U)>>2==0x1f){
        *(volatile uint32_t*)(iVar2+0x5000d000UL)=0;
      }
      iVar2=G1_NRF_GPIOTE0_S_BASE;
      uVar4=uVar4+1;
    }while(uVar4!=8);
    *(volatile uint32_t*)(0x5000d000UL+0x17c)=0;
    arch_irq_enable(0xd);
    *(volatile uint32_t*)(iVar2+0x304)=0x80000000;
    uVar3=0x0bad0000;
    *(volatile uint8_t*)(iVar1+0x78)=1;
    *(volatile uint32_t*)(iVar1+0x74)=1;
  }
  return uVar3;
}
