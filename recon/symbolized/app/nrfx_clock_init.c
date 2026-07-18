#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00065190 @ 0x00065190
 * public-name: nrfx_clock_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   nrfx_clock_init                          <= FUN_00065190 @ 0x00065190
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f6a4e                             @ 0x000f6a4e
 *   rodata_f6abf                             @ 0x000f6abf
 *   g_clock_cb                               @ 0x2000b31c
 *   nrfx_clock_module_initialized            @ 0x2000b320
 */
/* Reconstructed FUN_00065190 @ 0x65190  (parity: 300/300 trials, PROVEN)
 * Readable namespace target: g1_nrfx_clock_init_checked.
 */

#include <stdint.h>

extern void printk(uint32_t, uint32_t, uint32_t, uint32_t);
extern __attribute__((noreturn)) void assert_post_action(uint32_t, uint32_t);

uint32_t nrfx_clock_init(uintptr_t event_handler)
{
    volatile uintptr_t *handler = (volatile uintptr_t *)((unsigned long)&g_clock_cb) /*=0x2000b31c*/;
    volatile uint8_t *initialized = (volatile uint8_t *)((unsigned long)&nrfx_clock_module_initialized) /*=0x2000b320*/;

    if (event_handler == 0) {
        printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/, ((unsigned long)&rodata_f6abf) /*=0xf6abf*/, ((unsigned long)&rodata_f6a4e) /*=0xf6a4e*/, 0x115);
        assert_post_action(((unsigned long)&rodata_f6a4e) /*=0xf6a4e*/, 0x115);
    }

    if (*initialized != 0) {
        return 0x0bad000cUL;
    }

    *handler = event_handler;
    *initialized = 1;
    return 0x0bad0000UL;
}
