#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00065b18 @ 0x00065b18
 * public-name: gpiote_in_uninit
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_pin_idx                              <= FUN_00065434 @ 0x00065434
 *   gpiote_pin_is_used                       <= FUN_00065448 @ 0x00065448
 *   pin_in_use_by_te                         <= FUN_00065460 @ 0x00065460
 *   pin_te_get                               <= FUN_000654ac @ 0x000654ac
 *   gpiote_channel_release_if_unshared       <= FUN_00065504 @ 0x00065504
 *   nrfx_gpiote_trigger_disable              <= FUN_00065acc @ 0x00065acc
 *   gpiote_in_uninit                         <= FUN_00065b18 @ 0x00065b18
 * address symbols (name @ address):
 *   g_gpiote_cb                              @ 0x20002bc0
 */
/* Reconstructed FUN_00065b18 @ 0x65b18  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int get_pin_idx(int);
extern int gpiote_pin_is_used(void);
extern int pin_in_use_by_te(int);
extern int pin_te_get(int);
extern void gpiote_channel_release_if_unshared(int);
extern int FUN_00065584(int*);
extern void nrfx_gpiote_trigger_disable(int);
uint32_t gpiote_in_uninit(int param_1,int param_2){
  int local_c=param_2;
  int iVar2=gpiote_pin_is_used();
  uint32_t uVar3=0x0bad0004;
  if(iVar2!=0){
    nrfx_gpiote_trigger_disable(param_1);
    iVar2=pin_in_use_by_te(param_1);
    if(iVar2!=0){
      short sVar1=(short)pin_te_get(param_1);
      *(volatile uint32_t*)(sVar1*4+0x5000d510UL)=0;
      *(volatile uint32_t*)(sVar1*4+0x5000d510UL)=0;
    }
    gpiote_channel_release_if_unshared(param_1);
    iVar2=get_pin_idx(param_1);
    *(volatile uint16_t*)(((unsigned long)g_gpiote_cb) /*=0x20002bc0*/+(iVar2+8)*2)=0;
    local_c=param_1;
    iVar2=FUN_00065584(&local_c);
    iVar2=iVar2+local_c*4;
    *(volatile uint32_t*)(iVar2+0x200)=(0xfffcf0f0 & *(volatile uint32_t*)(iVar2+0x200))|2;
    uVar3=0x0bad0000;
  }
  return uVar3;
}
