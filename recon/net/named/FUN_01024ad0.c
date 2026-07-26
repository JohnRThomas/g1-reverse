/* readable reconstruction; identity: FUN_01024ad0 @ 0x01024ad0
 * public-name: FUN_01024ad0
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_radio_timer_active_flag            @ 0x21001bf7
 *   REG_41005000                             @ 0x41005000
 */
#include "../../headers/g1_nrf_regs.h"
/* net-core FUN_01024ad0 @ 0x1024ad0  (parity 300 trials PROVEN) */

#define DAT_01024ae8 ((unsigned int)G1_NRF_CLOCK_NS_BASE)
#define DAT_01024aec ((volatile unsigned char *)0x21001bf7)

unsigned char FUN_01024ad0(void)
{
    unsigned char bVar1;
    if (*(volatile int *)(DAT_01024ae8 + 0x100) == 0) {
        bVar1 = *DAT_01024aec;
    } else {
        bVar1 = 1;
    }
    return bVar1 & 1;
}
