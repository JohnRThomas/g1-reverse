/* readable reconstruction; identity: FUN_0101a0e8 @ 0x0101a0e8
 * public-name: radio_transition_overhead_get
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   radio_transition_overhead_get            <= FUN_0101a0e8 @ 0x0101a0e8
 *   controller_radio_work_pending            <= FUN_01025be0 @ 0x01025be0
 */
/* net-core FUN_0101a0e8 @ 0x101a0e8  (CFG-directed candidate) */

#include <stdint.h>

extern int32_t FUN_01025d28(void);
extern int32_t controller_radio_work_pending(void);
extern void FUN_01021908(int8_t *value);
extern void FUN_01021914(int8_t *value);

#define controller_radio_mode_active FUN_01025d28
#define controller_radio_work_pending controller_radio_work_pending
#define radio_tx_transition_pending_get FUN_01021908
#define radio_rx_transition_pending_get FUN_01021914

uint32_t radio_transition_overhead_get(void)
{
    uint32_t pending_overhead;
    uint32_t idle_overhead;
    volatile int8_t tx_pending;
    int8_t rx_pending;

    if (controller_radio_mode_active() != 0) {
        pending_overhead = 0xd9U;
        idle_overhead = 0xcfU;
    } else if (controller_radio_work_pending() != 0) {
        pending_overhead = 0xd0U;
        idle_overhead = 0xc6U;
    } else {
        pending_overhead = 0xc1U;
        idle_overhead = 0xb7U;
    }

    radio_tx_transition_pending_get((int8_t *)&tx_pending);
    int8_t tx_snapshot = tx_pending;
    radio_rx_transition_pending_get(&rx_pending);
    if ((int8_t)((uint8_t)tx_snapshot | (uint8_t)rx_pending) != 0)
        return pending_overhead;
    return idle_overhead;
}
