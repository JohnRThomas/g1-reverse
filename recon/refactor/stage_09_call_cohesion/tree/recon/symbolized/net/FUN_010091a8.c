#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010091a8 @ 0x010091a8
 * public-name: FUN_010091a8
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_layout_count_table                 @ 0x21000a30
 */
/* net-core FUN_010091a8 @ 0x010091a8 */
#include <stdint.h>

extern void thunk_FUN_0101621c(void);

uint32_t FUN_010091a8(void)
{
    volatile uint8_t *state = (volatile uint8_t *)((unsigned long)&g_net_layout_count_table) /*=0x21000a30*/;
    if (state[0x2d] == 0 && state[0x2c] == 0) {
        thunk_FUN_0101621c();
        return 0;
    }
    return UINT32_MAX;
}
