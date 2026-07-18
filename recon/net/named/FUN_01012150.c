/* readable reconstruction; identity: FUN_01012150 @ 0x01012150
 * public-name: FUN_01012150
 * durable-map: recon/catalogs/function_names_net.json
 */
/* FUN_01012150 @ 0x01012150: controller event-eligibility predicate. */
#include <stdint.h>

extern uint32_t sdc_hci_event_suppressed(void);

uint32_t FUN_01012150(const uint8_t *connection)
{
    if (connection[0x84] != 0u || connection[0xbc] != 0u) {
        return 1u;
    }
    if (connection[0xae] == 0u) {
        return 0u;
    }
    return (sdc_hci_event_suppressed() ^ 1u) & 0xffu;
}

/* Raw identity/back-map: FUN_01012150 @ 0x01012150, true extent 0x26. */
