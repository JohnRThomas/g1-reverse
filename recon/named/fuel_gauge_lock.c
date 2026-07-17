/* readable reconstruction; identity: FUN_000330c4 @ 0x000330c4
 * public-name: fuel_gauge_lock
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   fuel_gauge_lock                          <= FUN_000330c4 @ 0x000330c4
 *   lock_device_mutex                        <= FUN_0007c8b0 @ 0x0007c8b0
 * address symbols (name @ address):
 *   g_fuel_gauge_dev                         @ 0x20002424
 */
/* ABI-faithful reconstruction of FUN_000330c4 @ 0x330c4 (16 bytes). */
#include <stdint.h>

extern void lock_device_mutex(uint32_t enabled, uint32_t inherited_r1,
                         uint32_t inherited_r2, uint32_t inherited_r3);

uint32_t fuel_gauge_lock(uint32_t ignored, uint32_t inherited_r1,
                      uint32_t inherited_r2, uint32_t inherited_r3)
{
    (void)ignored;
    uint32_t enabled = *(volatile uint32_t *)0x20002424u;
    if (enabled != 0)
        lock_device_mutex(enabled, inherited_r1, inherited_r2, 0x20002424u);
    return 0;
}
