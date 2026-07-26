/* readable reconstruction; identity: FUN_01025344 @ 0x01025344
 * public-name: FUN_01025344
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_radio_timer_sync_state             @ 0x21001bf8
 */
/* net-core FUN_01025344 @ 0x1025344  (parity 300 trials PROVEN) */
#include <stdint.h>
#include "../../headers/g1_nrf_regs.h"

#define W32(a) (*(volatile uint32_t *)(a))

void FUN_01025344(void)
{
    volatile uint8_t * const flag = (uint8_t *)0x21001bf8;
    const uint32_t base1 = G1_NRF_RTC0_NS_BASE;
    const uint32_t base2 = G1_NRF_TIMER0_NS_BASE;

    if (*flag == 0) {
        W32(base1 + 0x348) = 0x30000;
        W32(base1 + 0x308) = 0x30000;
        W32(base1 + 0x140) = 0;
    } else {
        W32(base1 + 0x348) = 0x20000;
        W32(base1 + 0x308) = 0x20000;
    }

    W32(base2 + 0x308) = 0xffffffff;
    W32(base2 + 0x540) = 0;
    W32(base2 + 0x140) = 0;
    W32(base2 + 0x544) = 0;
    W32(base2 + 0x144) = 0;
    W32(base2 + 0x548) = 0;
    W32(base2 + 0x148) = 0;
    W32(base2 + 0x54c) = 0;
    W32(base2 + 0x14c) = 0;
}
