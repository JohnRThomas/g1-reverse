#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01019088 @ 0x01019088
 * public-name: FUN_01019088
 * durable-map: recon/catalogs/function_names_net.json
 */
/* CPUNET controller-state eligibility predicate @ 0x01019088.
 * Raw back-map: FUN_01019088=controller_state_is_eligible;
 * true executable extent 0x38. */
#include <stdbool.h>
#include <stdint.h>

bool FUN_01019088(void)
{
    volatile const uint8_t *const state =
        (volatile const uint8_t *)0x21000f90u;
    uint8_t mode = state[0x54];

    if (mode == 3u)
        return state[0x56] == 1u;
    if ((uint8_t)(mode - 1u) > 1u)
        return false;
    return (state[0x55] & 0xfdu) == 1u;
}
