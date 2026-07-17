/* readable reconstruction; identity: FUN_0100cb70 @ 0x0100cb70
 * public-name: FUN_0100cb70
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_radio_addr_match_tbl               @ 0x21000d18
 */
/* net-core FUN_0100cb70 @ 0x100cb70 */
#include <stdint.h>

extern void FUN_0100ab14(void *, void *, uint32_t);

void FUN_0100cb70(uint32_t value)
{
    volatile uint8_t *const state = (volatile uint8_t *)0x21000d18U;
    uint8_t count = state[1];
    uint32_t index = 0;
    while ((uint8_t)index < count) {
        uint8_t slot = (uint8_t)index;
        if (state[0x142U + slot] == 0) {
            FUN_0100ab14((void *)(state + 0x82U + 16U * slot),
                         (void *)(state + 0x10aU + 6U * slot), value);
            count = state[1];
        }
        ++index;
    }
}
