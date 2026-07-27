#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00017688 @ 0x00017688
 * public-name: gpio_pin_configure_17688
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gpio_pin_configure_17688                 <= FUN_00017688 @ 0x00017688
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99c53                             @ 0x00099c53
 *   rodata_99c84                             @ 0x00099c84   [INLINED -- G6 literal batch]
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_99cda                             @ 0x00099cda   [INLINED -- G6 literal batch]
 *   rodata_99d17                             @ 0x00099d17
 *   rodata_99d5e                             @ 0x00099d5e   [INLINED -- G6 literal batch]
 *   rodata_99dad                             @ 0x00099dad   [INLINED -- G6 literal batch]
 *   rodata_99de0                             @ 0x00099de0   [INLINED -- G6 literal batch]
 *   rodata_99e1e                             @ 0x00099e1e   [INLINED -- G6 literal batch]
 */
/* app-core FUN_00017688 @ 0x00017688 */
#include <stdint.h>
#include "../../headers/g1_log.h"

extern void assert_post_action(const void *, unsigned);

void gpio_pin_configure_17688(const uint8_t *pin, uint32_t flags)
{
    uintptr_t dev = *(const uint32_t *)pin;
    uint32_t combined = *(const uint16_t *)(pin + 6) | flags;
    unsigned line = pin[4];
    uint32_t bit;
    volatile uint32_t *enabled;
    volatile uint32_t *output;
    void (**api)(void);

    if ((combined & 0x30) == 0x30) {
        printk((unsigned long)((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, (void *)((unsigned long)"(flags & ((1 << 4) | (1 << 5))) != ((1 << 4) | (1 << 5))") /*=0x99c84*/, (void *)((unsigned long)&rodata_99c53) /*=0x99c53*/, 0x3ca);
        printk((unsigned long)((unsigned long)"\tPull Up and Pull Down should not be enabled simultaneously\n") /*=0x99cda*/);
        assert_post_action((void *)((unsigned long)&rodata_99c53) /*=0x99c53*/, 0x3ca);
    } else if ((combined & 0x30002) == 0x10002) {
        printk((unsigned long)((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, (void *)((unsigned long)&rodata_99d17) /*=0x99d17*/, (void *)((unsigned long)&rodata_99c53) /*=0x99c53*/, 0x3ce);
        printk((unsigned long)((unsigned long)"\tInput cannot be enabled for 'Open Drain', 'Open Source' modes without Output\n") /*=0x99d5e*/);
        assert_post_action((void *)((unsigned long)&rodata_99c53) /*=0x99c53*/, 0x3ce);
    } else if ((combined & 6) == 4) {
        printk((unsigned long)((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, (void *)((unsigned long)"(flags & (1 << 1)) != 0 || (flags & (1 << 2)) == 0") /*=0x99dad*/, (void *)((unsigned long)&rodata_99c53) /*=0x99c53*/, 0x3d1);
        assert_post_action((void *)((unsigned long)&rodata_99c53) /*=0x99c53*/, 0x3d1);
    }

    /* BRING-UP WIRING FIX (P4 iteration 5) — pointer-depth + indirect-call ABI.
     * Verified against the ORIGINAL image bytes at 0x17688 (capstone):
     *     17692: ldr  r0,[r0]          ; dev = spec->port
     *     1769e: ldr  r5,[r0,#0x10]    ; r5 = dev->data          (1 load)
     *     176a0: ldrd r7,r6,[r0,#4]    ; r7 = dev->config, r6 = dev->api
     *     17706: ldr  r3,[r7]          ; r3 = cfg->port_pin_mask (2nd load)
     *     1770a: tst  r4,r3
     *     17728: ldr  r3,[r5] ... 17732: str r3,[r5]   ; data->invert (2nd load)
     *     17734: ldr  r3,[r6] ; 1773a: bx r3   ; api->pin_configure(r0=dev,
     *                                          ;   r1=pin, r2=combined flags)
     * i.e. exactly Zephyr's gpio_pin_configure():
     *   __ASSERT(cfg->port_pin_mask & BIT(pin), "Unsupported pin");
     *   data->invert |= / &= ~BIT(pin);
     *   return api->pin_configure(port, pin, flags);
     * The reconstruction carried ONE POINTER LEVEL TOO MANY on `enabled` and
     * `output` (`**(uint32_t***)` yields a uint32_t*, and the later `*enabled`
     * made a THIRD load — our build emitted `ldr r3,[r3]; ldr r3,[r3]` where the
     * original has a single `ldr r3,[r7]`), so with a *correct* device pointer
     * it dereferenced the port_pin_mask VALUE (0xffffffff) instead of reading
     * it.  It also called `(*api)()` with no arguments, which in the original
     * codegen happened to leave r0/r1/r2 holding dev/pin/flags but in our
     * codegen leaves r0 = the spec pointer.  Both are corrected here (build /
     * wiring TU only; recon/app/src/FUN_00017688.c left untouched). */
    enabled = *(volatile uint32_t **)(dev + 4);   /* &cfg->port_pin_mask */
    api = *(void (***)(void))(dev + 8);
    output = *(volatile uint32_t **)(dev + 16);   /* &data->invert */
    bit = 1u << line;
    if ((*enabled & bit) == 0) {
        printk((unsigned long)((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, (void *)((unsigned long)"(cfg->port_pin_mask & (gpio_port_pins_t)(1UL << (pin))) != 0U") /*=0x99de0*/, (void *)((unsigned long)&rodata_99c53) /*=0x99c53*/, 0x3e4);
        printk((unsigned long)((unsigned long)"\tUnsupported pin\n") /*=0x99e1e*/);
        assert_post_action((void *)((unsigned long)&rodata_99c53) /*=0x99c53*/, 0x3e4);
    }
    if (combined & 1)
        *output |= bit;
    else
        *output &= ~bit;
    ((int (*)(uintptr_t, unsigned, uint32_t))(*api))(dev, line, combined);
}
