/* readable reconstruction; identity: FUN_01024aa8 @ 0x01024aa8
 * public-name: FUN_01024aa8
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_radio_timer_active_flag            @ 0x21001bf7
 *   REG_41005000                             @ 0x41005000
 */
#include "../../headers/g1_nrf_regs.h"
/* net-core FUN_01024aa8 @ 0x1024aa8  (parity 300 trials PROVEN) */

void FUN_01024aa8(void)
{
    volatile unsigned int * const p = (volatile unsigned int * const)G1_NRF_CLOCK_NS_BASE;
    volatile unsigned char * const q = (volatile unsigned char * const)0x21001bf7;
    p[1] = 1;
    p[0x40] = 0;
    q[0] = 0;
}
