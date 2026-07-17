/* Reconstructed __nrfy_internal_twim_events_process @ 0x8539a  (CFG-directed candidate) */
#include <stdint.h>
extern uintptr_t FUN_00085378(uintptr_t reg, uint32_t mask, uint32_t event, uint32_t *events);
uint32_t __nrfy_internal_twim_events_process(uintptr_t reg, uint32_t mask) {
    uint32_t events = 0;
    reg = FUN_00085378(reg, mask, 0x148u, &events);
    reg = FUN_00085378(reg, mask, 0x104u, &events);
    reg = FUN_00085378(reg, mask, 0x124u, &events);
    reg = FUN_00085378(reg, mask, 0x150u, &events);
    reg = FUN_00085378(reg, mask, 0x14cu, &events);
    reg = FUN_00085378(reg, mask, 0x160u, &events);
    (void)FUN_00085378(reg, mask, 0x15cu, &events);
    return events;
}
