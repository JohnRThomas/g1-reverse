/* readable reconstruction; identity: FUN_00067884 @ 0x00067884
 * public-name: nrfx_twim_enable
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   nrfx_twim_enable                         <= FUN_00067884 @ 0x00067884
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f6fef                             @ 0x000f6fef
 *   rodata_f7052                             @ 0x000f7052
 *   g_nrfx_twim_cb                           @ 0x2000b3cc
 */
/* Full reconstruction FUN_00067884 @ 0x67884, exact extent 60 bytes. */
#include <stdint.h>
#include "../headers/g1_log.h"
extern __attribute__((noreturn)) void assert_post_action(uintptr_t,uint32_t);
void nrfx_twim_enable(uintptr_t *device,uint32_t a,uint32_t b,uint32_t context){
 (void)a;(void)b; uint8_t channel=((uint8_t*)device)[4]; volatile uint8_t *state=(volatile uint8_t*)(0x2000b3ccu+channel*40u);
 if(state[0x22]!=1){printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"),0x000f7052u,0x000f6fefu,0x16b,context);assert_post_action(0x000f6fefu,0x16b);}
 *(volatile uint32_t*)(*device+0x500)=6;state[0x22]=2;
}
