/* readable reconstruction; identity: FUN_01009184 @ 0x01009184
 * public-name: FUN_01009184
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   thunk_FUN_0101dc1c                       <= FUN_010294ba @ 0x010294ba
 * address symbols (name @ address):
 *   g_net_layout_count_table                 @ 0x21000a30
 */
/* net-core FUN_01009184 @ 0x1009184 */
#include <stdint.h>

extern void thunk_FUN_0101dc1c(void);

uint32_t FUN_01009184(void)
{
    volatile uint8_t *state = (volatile uint8_t *)0x21000a30u;

    if (state[0x2d] == 0 && state[0x2c] == 0) {
        thunk_FUN_0101dc1c();
        return 0;
    }
    return UINT32_MAX;
}
