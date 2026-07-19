#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00065324 @ 0x00065324
 * public-name: nrfx_clock_stop
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   clock_stop                               <= FUN_00065000 @ 0x00065000
 *   nrfx_clock_stop                          <= FUN_00065324 @ 0x00065324
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f6a4e                             @ 0x000f6a4e
 *   rodata_f6acd                             @ 0x000f6acd
 *   nrfx_clock_module_initialized            @ 0x2000b320
 */
/* Reconstructed FUN_00065324 @ 0x65324  (parity: 300/300 trials, PROVEN)
 * Readable namespace target: g1_nrfx_clock_stop_checked.
 */
#include <stdint.h>
extern __attribute__((noreturn)) void assert_post_action(uint32_t,uint32_t);
extern void printk(uint32_t,uint32_t,uint32_t,uint32_t);
extern void clock_stop(int domain);

void nrfx_clock_stop(int domain)
{
    if (*(volatile uint8_t*)((unsigned long)&nrfx_clock_module_initialized) /*=0x2000b320*/ == 0) {
        printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/, ((unsigned long)&rodata_f6acd) /*=0xf6acd*/, ((unsigned long)&rodata_f6a4e) /*=0xf6a4e*/, 0x1ad);
        assert_post_action(((unsigned long)&rodata_f6a4e) /*=0xf6a4e*/, 0x1ad);
    }
    clock_stop(domain);
}
