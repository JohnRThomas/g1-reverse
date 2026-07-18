/* readable reconstruction; identity: FUN_01022a30 @ 0x01022a30
 * public-name: FUN_01022a30
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_libc_tz_calc_state                     @ 0x210016f0
 */
/* net-core FUN_01022a30 @ 0x01022a30 -- raw backmap retained. */
#include <stdint.h>

extern __attribute__((noreturn)) void FUN_010256dc(uint32_t, uint32_t, ...);
#define controller_fault FUN_010256dc

void FUN_01022a30(uint8_t enabled)
{
    volatile uint8_t *const controller = (volatile uint8_t *)0x210016f0u;
    if (controller[0x4a] == 0x20)
        controller_fault(0x70, 0x38b);
    controller[0x2a] = enabled;
}
