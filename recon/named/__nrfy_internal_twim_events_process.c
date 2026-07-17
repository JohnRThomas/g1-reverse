/* readable reconstruction; identity: FUN_0008539a @ 0x0008539a
 * public-name: __nrfy_internal_twim_events_process
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   __nrfy_internal_twim_event_handle        <= FUN_00085378 @ 0x00085378
 */
/* Reconstructed __nrfy_internal_twim_events_process @ 0x8539a  (CFG-directed candidate) */
#include <stdint.h>
extern uintptr_t __nrfy_internal_twim_event_handle(uintptr_t reg, uint32_t mask, uint32_t event, uint32_t *events);
uint32_t __nrfy_internal_twim_events_process(uintptr_t reg, uint32_t mask) {
    uint32_t events = 0;
    reg = __nrfy_internal_twim_event_handle(reg, mask, 0x148u, &events);
    reg = __nrfy_internal_twim_event_handle(reg, mask, 0x104u, &events);
    reg = __nrfy_internal_twim_event_handle(reg, mask, 0x124u, &events);
    reg = __nrfy_internal_twim_event_handle(reg, mask, 0x150u, &events);
    reg = __nrfy_internal_twim_event_handle(reg, mask, 0x14cu, &events);
    reg = __nrfy_internal_twim_event_handle(reg, mask, 0x160u, &events);
    (void)__nrfy_internal_twim_event_handle(reg, mask, 0x15cu, &events);
    return events;
}
