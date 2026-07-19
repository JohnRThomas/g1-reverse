#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_k_poll_event__param_0207               [param_0207; library]
 * Raw function identity: 0x00075574.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00075574 @ 0x00075574
 * public-name: k_poll_event_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   k_poll_event_init                        <= FUN_00075574 @ 0x00075574
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f871d                             @ 0x000f871d
 *   rodata_f8835                             @ 0x000f8835
 *   rodata_f8855                             @ 0x000f8855
 *   rodata_f887b                             @ 0x000f887b
 *   rodata_f889f                             @ 0x000f889f
 *   rodata_f88af                             @ 0x000f88af
 *   rodata_f88c2                             @ 0x000f88c2
 */
/* FUN_00075574 @ 0x00075574 — complete 98-byte reconstruction. */
#include <stdint.h>

extern void printk(uintptr_t, ...);
extern void assert_post_action(uintptr_t, uint32_t) __attribute__((noreturn));

void k_poll_event_init(uint8_t *object, uint32_t priority,
                  uint32_t reserved, uintptr_t handler)
{
    uint32_t line;

    if (reserved != 0) {
        printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/, ((unsigned long)&rodata_f8835) /*=0xf8835*/, ((unsigned long)&rodata_f871d) /*=0xf871d*/, 0x2du, handler);
        printk(((unsigned long)&rodata_f8855) /*=0xf8855*/);
        line = 0x2d;
    } else if (priority >= 0x40) {
        printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/, ((unsigned long)&rodata_f887b) /*=0xf887b*/, ((unsigned long)&rodata_f871d) /*=0xf871d*/, 0x2fu, handler);
        printk(((unsigned long)&rodata_f889f) /*=0xf889f*/);
        line = 0x2f;
    } else if (handler == 0) {
        printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/, ((unsigned long)&rodata_f88af) /*=0xf88af*/, ((unsigned long)&rodata_f871d) /*=0xf871d*/, 0x30u, handler);
        printk(((unsigned long)&rodata_f88c2) /*=0xf88c2*/);
        line = 0x30;
    } else {
        *(uint32_t *)(object + 8) = reserved;
        *(uint32_t *)(object + 12) = ((priority & 0x3fu) << 8) | object[12];
        *(uintptr_t *)(object + 16) = handler;
        return;
    }

    assert_post_action(((unsigned long)&rodata_f871d) /*=0xf871d*/, line);
}
