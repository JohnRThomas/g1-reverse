/* readable reconstruction; identity: FUN_00016834 @ 0x00016834
 * public-name: FUN_00016834
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   device_info                              @ 0x200069fc
 */
/* Reconstructed FUN_00016834 @ 0x16834 (uncatalogued exact tail entry). */

#include <stdint.h>

extern uint32_t FUN_00026100(void *, uint32_t, uint32_t, uint32_t); /* FUN_00026100 */

uint32_t FUN_00016834(uint32_t state, uint32_t unused1,
                      uint32_t arg2, uint32_t arg3)
{
    uint32_t owner = *(volatile uint32_t *)0x200069fcUL;
    uint32_t normalized;

    (void)unused1;
    (void)arg3;
    normalized = state == 1U ? 1U : (state == 2U ? 2U : 0U);
    return FUN_00026100((void *)(owner + 3812U),
                        normalized, arg2, owner);
}
