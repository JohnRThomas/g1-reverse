/* net-core FUN_0101df84 @ 0x101df84  (CFG-directed candidate) */

#include <stdint.h>
extern __attribute__((noreturn)) void sdc_assertion_fail(uint32_t, uint32_t) __asm__("FUN_01008d00");
extern uint8_t *controller_typed_handle_lookup(uint16_t, uint32_t, uint32_t, uint32_t) __asm__("FUN_01009d18");
extern int32_t FUN_01009d64(uint16_t, uint32_t);
extern int32_t FUN_010278e4(void *, void *);
/* Raw identity/back-map: FUN_0101df84 @ 0x0101df84. */
void controller_entry_links_release(uint8_t *entry, uint8_t *context,
                                    uint32_t lookup_arg, uint32_t lookup_tail)
{
    if (context[0x1cb] != 0 && context[0x1d5] != 0) return;
    if (entry == 0) {
        if (context[0x1c2] == 0) {
            uint8_t *owner = controller_typed_handle_lookup(*(uint16_t *)(context + 0x17c), 1, lookup_arg, lookup_tail);
            if (owner != 0 && FUN_010278e4(owner + 0x158, context + 0x1e5) == 0) sdc_assertion_fail(0x1a, 0x23);
        }
        if (FUN_01009d64(*(uint16_t *)(context + 0x180), 8) != 0) sdc_assertion_fail(0x1a, 0x4e);
        return;
    }
    if (entry[0] == 0) {
        if (context[0x1c2] == 0) {
            uint8_t *owner = controller_typed_handle_lookup(*(uint16_t *)(context + 0x17c), 1, lookup_arg, lookup_tail);
            if (owner != 0 && FUN_010278e4(owner + 0x158, context + 0x1e5) == 0) sdc_assertion_fail(0x1a, 0x23);
        }
        if (FUN_01009d64(*(uint16_t *)(context + 0x180), 8) != 0) sdc_assertion_fail(0x1a, 0x53);
        if (*(uint32_t *)(entry + 0x74) == 0 && FUN_01009d64(*(uint16_t *)(context + 0x17e), 7) != 0) sdc_assertion_fail(0x1a, 0x60);
        return;
    }
    if (context[0x1c0] == 0) {
        if (context[0x1c2] == 0) {
            uint8_t *owner = controller_typed_handle_lookup(*(uint16_t *)(context + 0x17c), 0, lookup_arg, lookup_tail);
            if (owner != 0 && FUN_010278e4(owner + 0x158, context + 0x1e5) == 0) sdc_assertion_fail(0x1a, 0x2b);
        }
        *(uint16_t *)(context + 0x17c) = 0xffffu;
    }
    __asm__ volatile(
        "movs r1, #0\n"
        "movs r2, #0\n"
        "movs r3, #0\n"
        "str.w r1, [%0, #0x178]\n"
        "strd r2, r3, [%0, #0x170]\n"
        : : "r"(context) : "r1", "r2", "r3", "memory");
}
extern __typeof(controller_entry_links_release) FUN_0101df84 __attribute__((alias("controller_entry_links_release")));
