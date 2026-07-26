/* readable reconstruction; identity: FUN_00065ff4 @ 0x00065ff4
 * public-name: nrf_gpio_pin_port_decode_65ff4
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   nrf_gpio_pin_port_decode_65ff4           <= FUN_00065ff4 @ 0x00065ff4
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f09d1                             @ 0x000f09d1
 *   rodata_f0a04                             @ 0x000f0a04   [INLINED -- G6 literal batch]
 */
/* Full reconstruction FUN_00065ff4 @ 0x65ff4, exact extent 72 bytes. */
#include <stdint.h>
#include "../headers/g1_log.h"
extern __attribute__((noreturn)) void assert_post_action(uintptr_t,uint32_t);
uintptr_t nrf_gpio_pin_port_decode_65ff4(uint32_t *descriptor,uint32_t a,uint32_t b,uint32_t context){
 (void)a;(void)b; uint32_t v=*descriptor,bit,idx=v&31; uintptr_t base;
 if((v>>5)==0){bit=UINT32_MAX>>((uint8_t)v);base=0x50842500u;}
 else if((v>>5)==1){v=idx;bit=0xffffu>>idx;base=0x50842800u;}
 else goto invalid;
 if(bit&1){*descriptor=v;return base;}
invalid:printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"),((unsigned long)"nrf_gpio_pin_present_check(*p_pin)"),0x000f09d1u,0x32f,context);assert_post_action(0x000f09d1u,0x32f);
}
