#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00067d84 @ 0x00067d84
 * public-name: nrfx_wdt_reload_value_set
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   __aeabi_uldivmod                         <= FUN_0000e244 @ 0x0000e244
 *   arch_irq_enable                          <= FUN_000500ac @ 0x000500ac
 *   nrfx_wdt_reload_value_set                <= FUN_00067d84 @ 0x00067d84
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f79c8                             @ 0x000f79c8
 *   rodata_f7a03                             @ 0x000f7a03
 *   m_dppi_channels                          @ 0x2000b41c
 */
/* Full reconstruction FUN_00067d84 @ 0x67d84, exact extent 102 bytes. */
#include <stdint.h>
extern uint64_t __aeabi_uldivmod(uint32_t,uint32_t,uint32_t,uint32_t);
extern void printk(uintptr_t,uintptr_t,uintptr_t,uint32_t,...);
extern __attribute__((noreturn)) void assert_post_action(uintptr_t,uint32_t);
extern void arch_irq_enable(int32_t,uint32_t,uint32_t,uint32_t);
void nrfx_wdt_reload_value_set(uintptr_t *device,const uint32_t *ticks){
 uint32_t upper=ticks[1]>>17;
 uint64_t scaled=__aeabi_uldivmod(ticks[1]<<15,upper,1000,0);
 if(upper>=1000){printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)&rodata_f7a03) /*=0xf7a03*/,((unsigned long)&rodata_f79c8) /*=0xf79c8*/,0x3f);assert_post_action(((unsigned long)&rodata_f79c8) /*=0xf79c8*/,0x3f);}
 uintptr_t registers=*device;*(volatile uint32_t*)(registers+0x50c)=ticks[0];
 *(volatile uint32_t*)(registers+0x504)=(uint32_t)scaled;
 uint32_t channel=((const uint8_t*)device)[4];
 if(*(volatile uint32_t*)(((unsigned long)&m_dppi_channels) /*=0x2000b41c*/+channel*8u+4)!=0){
  *(volatile uint32_t*)(registers+0x100)=0;
  arch_irq_enable((int32_t)(registers<<12)>>24,(uint32_t)(scaled>>32),channel,0);
  *(volatile uint32_t*)(registers+0x304)=1;
 }
}
