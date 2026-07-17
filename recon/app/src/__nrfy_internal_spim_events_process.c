/* __nrfy_internal_spim_events_process @ 0x0008523e; raw FUN_0008523e */
#include <stdint.h>

extern int __nrfy_internal_spim_event_handle(void *, uint32_t, uint32_t,
                                              uint32_t *); /* FUN_00085214 */

uint32_t __nrfy_internal_spim_events_process(void *spim, uint32_t mask,
                                              const void *transfer)
{
    uint32_t events = 0;

    __nrfy_internal_spim_event_handle(spim, mask, 0x14c, &events);
    int stopped = __nrfy_internal_spim_event_handle(spim, mask, 0x104, &events);
    int ended = __nrfy_internal_spim_event_handle(spim, mask, 0x118, &events);
    int invalidated = 0;

    if (ended && transfer) {
        if (stopped) {
            (void)*(volatile uint32_t *)((uint8_t *)spim + 0x53c);
        } else {
            (void)transfer;
        }
        invalidated = 1;
    }
    if (__nrfy_internal_spim_event_handle(spim, mask, 0x110, &events) &&
        transfer && !invalidated) {
        if (stopped) {
            (void)*(volatile uint32_t *)((uint8_t *)spim + 0x53c);
        } else {
            (void)transfer;
        }
    }
    __nrfy_internal_spim_event_handle(spim, mask, 0x120, &events);
    return events;
}
