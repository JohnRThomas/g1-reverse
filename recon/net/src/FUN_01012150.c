/* FUN_01012150 @ 0x01012150: controller event-eligibility predicate. */
#include <stdint.h>

extern uint32_t sdc_hci_event_suppressed(void);

uint32_t controller_event_is_eligible(const uint8_t *connection)
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
extern __typeof(controller_event_is_eligible) FUN_01012150
    __attribute__((alias("controller_event_is_eligible")));
