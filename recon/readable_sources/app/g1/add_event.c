#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_2          => struct g1_layout_event_registration__param_0415         [param_0415; G1-original]
 * Raw function identity: 0x00086778.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00086778 @ 0x00086778
 * public-name: add_event
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   add_event                                <= FUN_00086778 @ 0x00086778
 */
/* CPUAPP Zephyr poll add_event @ 0x00086778.
 * Raw/address back-map: FUN_00086778 / 0x00086778.
 */
#include <stdint.h>
extern int z_sched_prio_cmp(void *, void *); /* FUN_00086622 */
#define add_event add_event

void add_event(uint32_t *events, uint32_t *event_node, uint8_t *poller)
{
    uint32_t *tail = (uint32_t *)(uintptr_t)events[1];
    if ((uint32_t *)(uintptr_t)events[0] != events && tail != 0) {
        uint8_t *pending_poller = *(uint8_t **)((uint8_t *)tail + 8);
        if (pending_poller != 0) pending_poller -= 0x60;
        if (z_sched_prio_cmp(pending_poller, poller - 0x60) <= 0) {
            uint32_t *pending = (uint32_t *)(uintptr_t)events[0];
            while (pending != 0 && pending != events) {
                uint8_t *p = *(uint8_t **)((uint8_t *)pending + 8);
                if (p != 0) p -= 0x60;
                if (z_sched_prio_cmp(poller - 0x60, p) > 0) {
                    uint32_t *next = (uint32_t *)(uintptr_t)pending[1];
                    event_node[0] = (uint32_t)(uintptr_t)pending;
                    event_node[1] = (uint32_t)(uintptr_t)next;
                    next[0] = (uint32_t)(uintptr_t)event_node;
                    pending[1] = (uint32_t)(uintptr_t)event_node;
                    return;
                }
                if (pending == (uint32_t *)(uintptr_t)events[1]) break;
                pending = (uint32_t *)(uintptr_t)pending[0];
            }
        }
    }
    tail = (uint32_t *)(uintptr_t)events[1];
    event_node[0] = (uint32_t)(uintptr_t)events;
    event_node[1] = (uint32_t)(uintptr_t)tail;
    tail[0] = (uint32_t)(uintptr_t)event_node;
    events[1] = (uint32_t)(uintptr_t)event_node;
}
