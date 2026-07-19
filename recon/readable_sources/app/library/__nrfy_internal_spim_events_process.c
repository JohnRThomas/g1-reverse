#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0008523e @ 0x0008523e
 * public-name: __nrfy_internal_spim_events_process
 * durable-map: recon/catalogs/function_names_app.json
 */
/* __nrfy_internal_spim_events_process @ 0x0008523e; raw FUN_0008523e */
#include <stdint.h>

#ifdef G1_APP_SDK_INLINE_COHESION
/* Exact NCS 2.5.1 nrfy_spim.h local owner; raw FUN_00085214 @ 0x00085214. */
static __attribute__((always_inline)) inline int
__nrfy_internal_spim_event_handle(void *spim, uint32_t mask,
                                  uint32_t event, uint32_t *events)
{
    uint32_t event_mask = 1u << ((event - 0x100u) >> 2);
    volatile uint32_t *event_reg =
        (volatile uint32_t *)((uint8_t *)spim + event);
    if ((mask & event_mask) != 0u && *event_reg != 0u) {
        *event_reg = 0u;
        (void)*event_reg; /* nrf_event_readback */
        if (events != 0)
            *events |= event_mask;
        return 1;
    }
    return 0;
}
#else
extern int __nrfy_internal_spim_event_handle(void *, uint32_t, uint32_t,
                                              uint32_t *); /* FUN_00085214 */
#endif

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
