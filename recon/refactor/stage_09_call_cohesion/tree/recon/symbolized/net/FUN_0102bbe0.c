#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0102bbe0 @ 0x0102bbe0
 * public-name: FUN_0102bbe0
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0102bbe0 @ 0x102bbe0  (P4 iteration 24; parity 300/300 trials, 0 mismatches (branch-free leaf)) */
/* CPUNET ESB "peer-sync pending" flag read @ 0x0102bbe0.
 * Raw back-map: FUN_0102bbe0@0x0102bbe0; true extent 0xc (6 code bytes + a
 * nop pad before the literal pool at 0x0102bbe8 = 0x21004fa6).
 */
#include <stdint.h>

unsigned int FUN_0102bbe0(void)
{
    return *(volatile uint8_t *)((unsigned long)&g_net_evt_last_notified_state) /*=0x21004fa6*/;
}
