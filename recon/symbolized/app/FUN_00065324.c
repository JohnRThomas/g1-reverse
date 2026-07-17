#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00065324 @ 0x00065324
 * public-name: FUN_00065324
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f6a4e                             @ 0x000f6a4e
 *   rodata_f6acd                             @ 0x000f6acd
 *   nrfx_clock_module_initialized            @ 0x2000b320
 */
/* Reconstructed FUN_00065324 @ 0x65324  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern __attribute__((noreturn)) void assert_post_action(uint32_t,uint32_t);
extern void printk(uint32_t,uint32_t,uint32_t,uint32_t);
extern void FUN_00065000(int,int);

void FUN_00065324(int param_1, int param_2)
{
    if (*(volatile uint8_t*)((unsigned long)&nrfx_clock_module_initialized) /*=0x2000b320*/ == 0) {
        printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/, ((unsigned long)&rodata_f6acd) /*=0xf6acd*/, ((unsigned long)&rodata_f6a4e) /*=0xf6a4e*/, 0x1ad);
        assert_post_action(((unsigned long)&rodata_f6a4e) /*=0xf6a4e*/, 0x1ad);
    }
    FUN_00065000(param_1, param_2);
}
