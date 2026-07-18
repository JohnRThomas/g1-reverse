/* readable reconstruction; identity: FUN_010283a4 @ 0x010283a4
 * public-name: FUN_010283a4
 * durable-map: recon/catalogs/function_names_net.json
 */
/* controller_state_is_4_or_5 @ 0x010283a4; raw FUN_010283a4.
 * Retained private-controller reconstruction; exact executable extent 0x14.
 */
#include <stdint.h>

extern uint32_t FUN_0101b74c(void);
#define controller_state_is_4_or_5 FUN_010283a4

uint32_t controller_state_is_4_or_5(void)
{
    uint8_t state = (uint8_t)FUN_0101b74c();
    return (uint8_t)(state - 4u) < 2u ? 1u : 0u;
}
