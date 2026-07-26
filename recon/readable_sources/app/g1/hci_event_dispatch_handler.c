#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_2          => struct g1_layout_net_buf__param_0172                    [param_0172; library]
 * Raw function identity: 0x00053658.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00053658 @ 0x00053658
 * public-name: hci_event_dispatch_handler
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   log_unhandled_hci_event                  <= FUN_00053580 @ 0x00053580
 *   hci_event_dispatch_handler               <= FUN_00053658 @ 0x00053658
 *   bt_log_forward_3arg                      <= FUN_00080ea2 @ 0x00080ea2
 * address symbols (name @ address):
 *   rodata_88138                             @ 0x00088138
 *   rodata_f2e62                             @ 0x000f2e62   [INLINED -- G6 literal batch]
 */
/* Full reconstruction FUN_00053658 @ 0x00053658 (88-byte exact extent). */
#include <stdint.h>

extern void log_unhandled_hci_event(uint32_t event);
extern void bt_log_forward_3arg(uintptr_t module, uint32_t level, const void *record);

struct log_record4 { uint32_t count, format, available, event; };

void hci_event_dispatch_handler(uint32_t event, void *buffer,
                  const uint8_t *handlers, uint32_t handler_count)
{
    const uint8_t *end = handlers + handler_count * 8u;

    while (handlers != end) {
        if (handlers[0] == event) {
            uint32_t available = *(const uint16_t *)((const uint8_t *)buffer + 0x10);
            if (available < handlers[1]) {
                struct log_record4 record = {4, ((unsigned long)"Too small (%u bytes) event 0x%02x") /*=0xf2e62*/, available, event};
                bt_log_forward_3arg(((unsigned long)&rodata_88138) /*=0x88138*/, 0x2040u, &record);
            } else {
                ((void (*)(void *))*(const uintptr_t *)(handlers + 4))(buffer);
            }
            return;
        }
        handlers += 8;
    }
    log_unhandled_hci_event(event);
}
