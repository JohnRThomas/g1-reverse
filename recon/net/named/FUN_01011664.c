/* readable reconstruction; identity: FUN_01011664 @ 0x01011664
 * public-name: FUN_01011664
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   rodata_1011add                           @ 0x01011add
 *   g_net_own_addr_info                      @ 0x21000f20
 */
/* net-core FUN_01011664 @ 0x01011664, true executable extent 0xba. */
#include <stdint.h>

extern void sdc_ext_adv_reschedule(void *set, uint32_t terminate); /* FUN_010140ec */
extern void sdc_llcp_stop_rx_timeout(void);                        /* FUN_010208b0 */
extern void sdc_llcp_release_rx_context(void);                     /* FUN_0101fca8 */
extern uint32_t sdc_hci_event_suppressed(void);                    /* FUN_0101f888 */
extern void sdc_work_submit(void *work, uintptr_t callback, uint32_t priority); /* FUN_0100ef88 */

#define RADIO_STATE ((volatile uint8_t *)(uintptr_t)0x21000f20u)

void FUN_01011664(uint8_t *set)
{
    uint16_t count = (uint16_t)(*(uint16_t *)(set + 0x40) + 1u);
    *(uint16_t *)(set + 0x40) = count;

    if (RADIO_STATE[0x12] != 0u) {
        sdc_llcp_stop_rx_timeout();
        sdc_llcp_release_rx_context();
        RADIO_STATE[0x12] = 0u;
    }
    RADIO_STATE[4] = 0u;
    if (set[0x79] != 0u) {
        sdc_ext_adv_reschedule(set, 1u);
        return;
    }
    if ((set[0x0d] == 0u) || (count < set[0x0d])) {
        sdc_ext_adv_reschedule(set, 0u);
        return;
    }
    sdc_ext_adv_reschedule(set, 1u);
    if ((*(uint16_t *)(set + 2) & 1u) != 0u) {
        uint16_t value = **(uint16_t **)(set + 0x1c);
        if (sdc_hci_event_suppressed() != 0u) {
            return;
        }
        set[0xaf] = 0x43u;
        set[0xb0] = set[0];
        *(uint16_t *)(set + 0xb1) = value;
    } else {
        if (sdc_hci_event_suppressed() != 0u) {
            return;
        }
        set[0xaf] = 0x43u;
        set[0xb0] = set[0];
        *(uint16_t *)(set + 0xb1) = 0xffffu;
    }
    set[0xb3] = (set[0x0d] != 0u) ? set[0x40] : 0u;
    sdc_work_submit(set + 0xa6, (uintptr_t)0x01011addu, 2u);
}
