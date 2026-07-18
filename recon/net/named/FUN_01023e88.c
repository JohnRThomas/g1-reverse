/* readable reconstruction; identity: FUN_01023e88 @ 0x01023e88
 * public-name: FUN_01023e88
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_libc_tz_calc_state                     @ 0x210016f0
 */
/* net-core FUN_01023e88 @ 0x01023e88 -- raw backmap retained. */
#include <stdint.h>

extern __attribute__((noreturn)) void FUN_010256dc(uint32_t, uint32_t, ...);
#define controller_fault FUN_010256dc

uint8_t FUN_01023e88(void)
{
    volatile uint8_t *const controller = (volatile uint8_t *)0x210016f0u;
    if (controller[0x4a] == 0x20)
        controller_fault(0x70, 0xbad);
    return controller[0x20];
}
