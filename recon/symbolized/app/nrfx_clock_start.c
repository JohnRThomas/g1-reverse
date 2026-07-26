#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0006522c @ 0x0006522c
 * public-name: nrfx_clock_start
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   clock_stop                               <= FUN_00065000 @ 0x00065000
 *   nrfx_clock_start                         <= FUN_0006522c @ 0x0006522c
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_10000                             @ 0x00010000
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f6a4e                             @ 0x000f6a4e
 *   rodata_f6acd                             @ 0x000f6acd
 *   rodata_f7a30                             @ 0x000f7a30
 *   nrfx_clock_module_initialized            @ 0x2000b320
 */
/* Reconstructed FUN_0006522c @ 0x6522c.
 * Firmware checked nrfx_clock_start; raw/address back-map is preserved.
 */
#include <stdint.h>
#include "../../headers/g1_log.h"

#define CLOCK ((volatile uint32_t *)0x50005000UL)
extern void clock_stop(int domain);
extern __attribute__((noreturn)) void assert_post_action(uint32_t, uint32_t);

void nrfx_clock_start(unsigned domain)
{
    if (*(volatile uint8_t *)((unsigned long)&nrfx_clock_module_initialized) /*=0x2000b320*/ == 0u) {
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)&rodata_f6acd) /*=0xf6acd*/, ((unsigned long)&rodata_f6a4e) /*=0xf6a4e*/, 0x168);
        assert_post_action(((unsigned long)&rodata_f6a4e) /*=0xf6a4e*/, 0x168);
    }

    switch (domain) {
    case 0: {
        uint32_t source;
        uint32_t status = CLOCK[0x418 / 4];
        if ((status & ((unsigned long)&rodata_10000) /*=0x10000*/) != 0u) {
            source = status & 3u;
            if (source != 1u && source != 2u) {
                clock_stop(0);
                source = 1u;
            }
        } else if ((CLOCK[0x414 / 4] & 1u) != 0u) {
            source = CLOCK[0x41c / 4] & 3u;
            if (source == 1u || source == 2u) {
                CLOCK[0x304 / 4] = 2u;
                return;
            }
            source = 1u;
        } else {
            source = 1u;
        }
        CLOCK[0x518 / 4] = source;
        CLOCK[0x104 / 4] = 0u;
        (void)CLOCK[0x104 / 4];
        CLOCK[0x304 / 4] = 2u;
        CLOCK[0x008 / 4] = 1u;
        return;
    }
    case 1:
        CLOCK[0x100 / 4] = 0u;
        (void)CLOCK[0x100 / 4];
        CLOCK[0x304 / 4] = 1u;
        CLOCK[0x000 / 4] = 1u;
        return;
    case 2:
        CLOCK[0x124 / 4] = 0u;
        (void)CLOCK[0x124 / 4];
        CLOCK[0x304 / 4] = 0x200u;
        CLOCK[0x020 / 4] = 1u;
        return;
    case 3:
        CLOCK[0x120 / 4] = 0u;
        (void)CLOCK[0x120 / 4];
        CLOCK[0x304 / 4] = 0x100u;
        CLOCK[0x018 / 4] = 1u;
        return;
    default:
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)&rodata_f7a30) /*=0xf7a30*/, ((unsigned long)&rodata_f6a4e) /*=0xf6a4e*/, 0x1a6);
        assert_post_action(((unsigned long)&rodata_f6a4e) /*=0xf6a4e*/, 0x1a6);
    }
}
