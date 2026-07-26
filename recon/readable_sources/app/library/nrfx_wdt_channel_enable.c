#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00067e30 @ 0x00067e30
 * public-name: nrfx_wdt_channel_enable
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   nrfx_wdt_channel_enable                  <= FUN_00067e30 @ 0x00067e30
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f7052                             @ 0x000f7052
 *   rodata_f79c8                             @ 0x000f79c8
 *   rodata_f7a1b                             @ 0x000f7a1b
 *   m_dppi_channels                          @ 0x2000b41c
 */
/* Full reconstruction FUN_00067e30 @ 0x67e30, exact extent 70 bytes. */
#include <stdint.h>
#include "../../../headers/g1_log.h"
extern __attribute__((noreturn)) void assert_post_action(uintptr_t,uint32_t);
void nrfx_wdt_channel_enable(uintptr_t *device,uint32_t a,uint32_t b,uint32_t context){
 (void)a;(void)b;uint32_t ch=((uint8_t*)device)[4];volatile uint8_t *s=(volatile uint8_t*)(((unsigned long)&m_dppi_channels) /*=0x2000b41c*/+ch*8u);
 if(s[1]==0){printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)&rodata_f7a1b) /*=0xf7a1b*/,((unsigned long)&rodata_f79c8) /*=0xf79c8*/,0x8c,context);assert_post_action(((unsigned long)&rodata_f79c8) /*=0xf79c8*/,0x8c);}
 if(s[0]==1){*(volatile uint32_t*)*device=1;s[0]=2;return;}
 printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)&rodata_f7052) /*=0xf7052*/,((unsigned long)&rodata_f79c8) /*=0xf79c8*/,0x8d,context);assert_post_action(((unsigned long)&rodata_f79c8) /*=0xf79c8*/,0x8d);
}
