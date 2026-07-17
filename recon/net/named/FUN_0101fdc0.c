/* readable reconstruction; identity: FUN_0101fdc0 @ 0x0101fdc0
 * public-name: FUN_0101fdc0
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_radio_pending_reset_flag           @ 0x210014dc
 */
/* Reconstructed internal net function FUN_0101fdc0 @ 0x0101fdc0.
 * Code [0x0101fdc0,0x0101fdcc), 12 bytes; one literal at
 * [0x0101fdcc,0x0101fdd0), before FUN_0101fdd0. */
#include <stdint.h>
void FUN_0101fdc0(void)
{
    volatile uint8_t *state=(volatile uint8_t *)0x210014dcu;
    *(volatile uint16_t *)state=0;
    state[2]=0;
}
