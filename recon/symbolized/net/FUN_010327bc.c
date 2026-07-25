#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010327bc @ 0x010327bc
 * public-name: FUN_010327bc
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_010327bc @ 0x10327bc  (P4 iteration 24; parity 300/300 trials, 0 mismatches) */
/* CPUNET ESB radio-owner TIMER callback @ 0x010327bc.
 * Raw back-map: FUN_010327bc@0x010327bc; true extent 0x18 (literal
 * 0x010327d4 = 0x21000698, the nrfx_timer_t instance).
 * FUN_010333b4 installs it as the RUNTIME Thumb pointer 0x01032fbd
 * (= analysis 0x010327bc | 1) through nrfx_timer_init's handler argument.
 * It clears TIMER EVENTS_COMPARE[1] when INTENSET bit 17 (COMPARE1) is set.
 */
#include <stdint.h>

void FUN_010327bc(void)
{
    volatile uint32_t *volatile *const instance =
        (volatile uint32_t *volatile *)((unsigned long)&g_net_log_msg_ctx) /*=0x21000698*/;
    volatile uint32_t *const timer = *instance;

    if ((timer[0x304u / 4u] & (1u << 17)) != 0u) {
        timer[0x144u / 4u] = 0;
        (void)timer[0x144u / 4u];
    }
}
