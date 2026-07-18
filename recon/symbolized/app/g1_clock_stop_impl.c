#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00065000 @ 0x00065000
 * public-name: g1_clock_stop_impl
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   g1_clock_stop_impl                       <= FUN_00065000 @ 0x00065000
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   thunk_FUN_00086384                       <= FUN_000850d8 @ 0x000850d8
 * address symbols (name @ address):
 *   rodata_10000                             @ 0x00010000
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f6a4e                             @ 0x000f6a4e
 *   rodata_f6a8b                             @ 0x000f6a8b
 *   rodata_f7a30                             @ 0x000f7a30
 */
/* Reconstructed private nrfx clock_stop implementation @ 0x00065000.
 * Raw/address back-map: FUN_00065000 / 0x00065000.
 * Readable namespace target: g1_clock_stop_impl (not SDK nrfx_clock_stop).
 */
#include <stdint.h>

#define CLOCK_BASE_ADDRESS 0x50005000u /*=0x50005000*/
#define CLOCK_REGISTER(offset) \
    (*(volatile uint32_t *)(CLOCK_BASE_ADDRESS + (offset)))

#define nrfx_delay_us thunk_FUN_00086384 /*=0x000850d8*/
#define nrfx_assert_report printk /*=0x0007e2fa*/
#define nrfx_assert_abort assert_post_action /*=0x0007e2ec*/
extern void nrfx_delay_us(uint32_t microseconds);
extern void nrfx_assert_report(uint32_t format, uint32_t source,
                               uint32_t header, uint32_t line);
extern __attribute__((noreturn)) void nrfx_assert_abort(uint32_t header,
                                                        uint32_t line);

enum clock_domain_raw {
    CLOCK_DOMAIN_LFCLK = 0,
    CLOCK_DOMAIN_HFCLK = 1,
    CLOCK_DOMAIN_HFCLK192M = 2,
    CLOCK_DOMAIN_HFCLKAUDIO = 3
};

static void clock_domain_assert(uint32_t header, uint32_t line)
{
    nrfx_assert_report(((unsigned long)&rodata_99cbd) /*=0x99cbd*/, ((unsigned long)&rodata_f7a30) /*=0xf7a30*/, header, line);
    nrfx_assert_abort(header, line);
}

#define g1_clock_stop_impl g1_clock_stop_impl
void g1_clock_stop_impl(enum clock_domain_raw domain)
{
    switch (domain) {
    case CLOCK_DOMAIN_LFCLK:
        CLOCK_REGISTER(0x308u) = 2u;
        CLOCK_REGISTER(0x104u) = 0u;
        (void)CLOCK_REGISTER(0x104u);
        CLOCK_REGISTER(0x00cu) = 1u;
        break;
    case CLOCK_DOMAIN_HFCLK:
        CLOCK_REGISTER(0x308u) = 1u;
        CLOCK_REGISTER(0x100u) = 0u;
        (void)CLOCK_REGISTER(0x100u);
        CLOCK_REGISTER(0x004u) = 1u;
        break;
    case CLOCK_DOMAIN_HFCLK192M:
        CLOCK_REGISTER(0x308u) = 0x200u;
        CLOCK_REGISTER(0x124u) = 0u;
        (void)CLOCK_REGISTER(0x124u);
        CLOCK_REGISTER(0x024u) = 1u;
        break;
    case CLOCK_DOMAIN_HFCLKAUDIO:
        CLOCK_REGISTER(0x308u) = 0x100u;
        CLOCK_REGISTER(0x120u) = 0u;
        (void)CLOCK_REGISTER(0x120u);
        CLOCK_REGISTER(0x01cu) = 1u;
        break;
    default:
        clock_domain_assert(((unsigned long)&rodata_f6a4e) /*=0xf6a4e*/, 216u);
    }

    uint32_t remaining_attempts = 10000u;
    do {
        uint32_t state;
        uint32_t source = 1u;

        switch (domain) {
        case CLOCK_DOMAIN_LFCLK:
            state = CLOCK_REGISTER(0x418u);
            break;
        case CLOCK_DOMAIN_HFCLK:
            state = CLOCK_REGISTER(0x40cu);
            source = CLOCK_REGISTER(0x40cu) & 1u;
            break;
        case CLOCK_DOMAIN_HFCLK192M:
            state = CLOCK_REGISTER(0x45cu);
            break;
        case CLOCK_DOMAIN_HFCLKAUDIO:
            state = CLOCK_REGISTER(0x454u);
            break;
        default:
            clock_domain_assert(((unsigned long)&rodata_f6a8b) /*=0xf6a8b*/, 971u);
        }

        if ((state & ((unsigned long)&rodata_10000) /*=0x10000*/) == 0u ||
            (domain == CLOCK_DOMAIN_HFCLK && source != 1u)) {
            break;
        }
        nrfx_delay_us(1u);
    } while (--remaining_attempts != 0u);
}
