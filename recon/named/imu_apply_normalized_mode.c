/* readable reconstruction; identity: FUN_00016834 @ 0x00016834
 * public-name: imu_apply_normalized_mode
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   imu_apply_normalized_mode                <= FUN_00016834 @ 0x00016834
 *   update_imu_mode                          <= FUN_00026100 @ 0x00026100
 * address symbols (name @ address):
 *   device_info                              @ 0x200069fc
 */
/* Reconstructed FUN_00016834 @ 0x16834 (uncatalogued exact tail entry). */

#include <stdint.h>

extern uint32_t update_imu_mode(void *, uint32_t, uint32_t, uint32_t); /* FUN_00026100 */

uint32_t imu_apply_normalized_mode(uint32_t state, uint32_t unused1,
                      uint32_t arg2, uint32_t arg3)
{
    uint32_t owner = *(volatile uint32_t *)0x200069fcUL;
    uint32_t normalized;

    (void)unused1;
    (void)arg3;
    normalized = state == 1U ? 1U : (state == 2U ? 2U : 0U);
    return update_imu_mode((void *)(owner + 3812U),
                        normalized, arg2, owner);
}
