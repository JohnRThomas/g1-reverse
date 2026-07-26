#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00067304 @ 0x00067304
 * public-name: nrfx_spim_xfer
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   nrfx_spim_xfer                           <= FUN_00067304 @ 0x00067304
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   __nrfy_internal_spim_events_process      <= FUN_0008523e @ 0x0008523e
 *   spim_abort                               <= FUN_000852ba @ 0x000852ba
 *   nrf_gpio_pin_outset                      <= FUN_000852e6 @ 0x000852e6
 *   nrf_gpio_pin_set                         <= FUN_000852fe @ 0x000852fe
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f6df0                             @ 0x000f6df0
 *   rodata_f6e3a                             @ 0x000f6e3a
 *   rodata_f6e66                             @ 0x000f6e66
 *   rodata_f6ead                             @ 0x000f6ead
 *   rodata_f6ef4                             @ 0x000f6ef4
 *   rodata_f6fa3                             @ 0x000f6fa3
 *   rodata_f6fd9                             @ 0x000f6fd9
 *   g_sram_base_word                         @ 0x20000000
 *   g_nrfx_spim_cb                           @ 0x2000b384
 */
/* Full reconstruction FUN_00067304 @ 0x00067304 (498-byte exact extent). */
#include <stdint.h>

extern void printk(uintptr_t, ...);
extern void assert_post_action(uintptr_t, uint32_t) __attribute__((noreturn));
extern void __nrfy_internal_spim_events_process(void *, uint32_t, const void *);
extern void spim_abort(void *, void *);
extern void nrf_gpio_pin_outset(void);
extern void nrf_gpio_pin_set(void);

static void fatal(uintptr_t message, uint32_t line)
{
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, message, ((unsigned long)&rodata_f6df0) /*=0xf6df0*/, line);
    assert_post_action(((unsigned long)&rodata_f6df0) /*=0xf6df0*/, line);
}

uint32_t nrfx_spim_xfer(uint32_t *owner, const uint32_t descriptor[4],
                      uint32_t flags, uint32_t fourth)
{
    volatile uint8_t *channels = (volatile uint8_t *)((unsigned long)&g_nrfx_spim_cb) /*=0x2000b384*/;
    uint32_t channel = *((uint8_t *)owner + 4);
    volatile uint8_t *state = channels + channel * 0x24u;
    uint32_t saved[4] = {(uint32_t)(uintptr_t)owner,
                         (uint32_t)(uintptr_t)descriptor, flags, fourth};

    if (!state[0x1c]) fatal(((unsigned long)&rodata_f6e3a) /*=0xf6e3a*/, 0x314);
    if (!descriptor[0] && descriptor[1]) fatal(((unsigned long)&rodata_f6e66) /*=0xf6e66*/, 0x315);
    int shift = *(const int8_t *)(((unsigned long)&rodata_f6fd9) /*=0xf6fd9*/ + channel);
    if ((!descriptor[2] && descriptor[3]) ||
        (descriptor[2] ? (descriptor[3] >> shift) : (descriptor[1] >> shift)))
        fatal(descriptor[2] ? ((unsigned long)&rodata_f6ef4) /*=0xf6ef4*/ : ((unsigned long)&rodata_f6ead) /*=0xf6ead*/,
              descriptor[2] ? 0x317u : 0x316u);
    if ((flags & 8u) && *(volatile int32_t *)(state + 0x20) != -1)
        fatal(((unsigned long)&rodata_f6fa3) /*=0xf6fa3*/, 0x31au);

    if (state[0x1d]) return 0x0bad000bu;
    if (*(volatile uint32_t *)state && !(flags & 0x14u)) state[0x1d] = 1;
    ((volatile uint32_t *)state)[3] = descriptor[0];
    ((volatile uint32_t *)state)[4] = descriptor[1];
    ((volatile uint32_t *)state)[5] = descriptor[2];
    ((volatile uint32_t *)state)[6] = descriptor[3];

    if (*(volatile int32_t *)(state + 0x20) != -1) {
        if (state[0x1f]) nrf_gpio_pin_outset(); else nrf_gpio_pin_set();
    }
    uint8_t *object = (uint8_t *)(uintptr_t)*owner;
    if ((descriptor[0] && (descriptor[0] & 0xe0000000u) != ((unsigned long)&g_sram_base_word) /*=0x20000000*/) ||
        (descriptor[2] && (descriptor[2] & 0xe0000000u) != ((unsigned long)&g_sram_base_word) /*=0x20000000*/)) {
        state[0x1d] = 0;
        return 0x0bad000au;
    }

    *(uint32_t *)(object + 0x550) = !!(flags & 1u);
    *(uint32_t *)(object + 0x540) = !!(flags & 2u);
    *(uint32_t *)(object + 0x544) = descriptor[0];
    *(uint32_t *)(object + 0x548) = descriptor[1];
    *(uint32_t *)(object + 0x534) = descriptor[2];
    *(uint32_t *)(object + 0x538) = descriptor[3];
    *(uint32_t *)(object + 0x118) = 0;
    *(uint32_t *)(object + 0x500) = 7;

    if (!(flags & 8u)) {
        *(uint32_t *)(object + 0x10) = 1;
        if (!*(volatile uint32_t *)state) {
            while (!*(volatile uint32_t *)(object + 0x118)) { }
            __nrfy_internal_spim_events_process(object, 0x40, saved);
        }
        if (!*(volatile uint32_t *)state) {
            if (*(volatile int32_t *)(state + 0x20) != -1) {
                if (state[0x1f]) nrf_gpio_pin_set(); else nrf_gpio_pin_outset();
            }
            spim_abort(object, (void *)state);
            return 0x0bad0000u;
        }
    } else if (!*(volatile uint32_t *)state) {
        if (*(volatile int32_t *)(state + 0x20) != -1) {
            if (state[0x1f]) nrf_gpio_pin_set(); else nrf_gpio_pin_outset();
        }
        return 0x0bad0000u;
    }
    if (flags & 4u) *(uint32_t *)(object + 0x308) = 0x40;
    else *(uint32_t *)(object + 0x304) = 0x40;
    return 0x0bad0000u;
}
