#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00067e8c @ 0x00067e8c
 * public-name: g1_recon_nrfx_wdt_channel_alloc
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   g1_recon_nrfx_wdt_channel_alloc          <= FUN_00067e8c @ 0x00067e8c
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f7052                             @ 0x000f7052
 *   rodata_f79c8                             @ 0x000f79c8
 *   rodata_f7a32                             @ 0x000f7a32
 *   m_dppi_channels                          @ 0x2000b41c
 */
/* Reconstructed FUN_00067e8c @ 0x67e8c  (parity: 1/400 trials, PROVEN) */
#include <stdint.h>
#include "../../headers/g1_log.h"
typedef unsigned int uint;
extern void assert_post_action(const char *, unsigned int);
uint32_t g1_recon_nrfx_wdt_channel_alloc(int* param_1, uint8_t* param_2){
  uint8_t r4byte=*(volatile uint8_t*)((char*)param_1+4);
  if(param_2==0){
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)&rodata_f7a32) /*=0xf7a32*/,((unsigned long)&rodata_f79c8) /*=0xf79c8*/,0xa2);
    assert_post_action(((unsigned long)&rodata_f79c8) /*=0xf79c8*/,0xa2);
  }
  int iVar6=(int)(((unsigned long)&m_dppi_channels) /*=0x2000b41c*/ + (uint)r4byte*8);
  while(*(volatile uint8_t*)iVar6 != 1){
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)&rodata_f7052) /*=0xf7052*/,((unsigned long)&rodata_f79c8) /*=0xf79c8*/,0xa3);
    assert_post_action(((unsigned long)&rodata_f79c8) /*=0xf79c8*/,0xa3);
  }
  uint8_t bVar1=*(volatile uint8_t*)(iVar6+1);
  uint32_t uVar4=0x0bad0002;
  if(bVar1<8){
    *param_2=bVar1;
    *(volatile uint8_t*)(iVar6+1)=bVar1+1;
    uVar4=0x0bad0000;
    *(volatile uint32_t*)(*(volatile int*)param_1+0x508)=(1u<<bVar1)|*(volatile uint32_t*)(*(volatile int*)param_1+0x508);
  }
  return uVar4;
}
