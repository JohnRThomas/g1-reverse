/* net-core FUN_0101bbc8 @ 0x0101bbc8
 * Readable identity: controller_margin_packet_time_get.
 * Raw callee backmaps: FUN_0101a130=radio_slot_margin_get,
 * FUN_0100f5b4=controller_payload_time_get.
 */
#include <stdint.h>

extern uint32_t radio_slot_margin_get(void);
extern uint32_t FUN_0100f5b4(const uint32_t *timing, uint32_t overhead);

#define controller_payload_time_get FUN_0100f5b4

uint32_t FUN_0101bbc8(const uint32_t *timing)
{
    uint32_t overhead = radio_slot_margin_get() + 0x111u;
    uint32_t duration = controller_payload_time_get(timing, overhead);

    if (duration >= 0xa90u) {
        duration = 0xa90u;
    }
    return (uint16_t)duration;
}
