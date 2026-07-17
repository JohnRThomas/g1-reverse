/* Reconstructed send_touch_click_event @ 0x7c058
 * (raw identity FUN_0007c058; CFG-directed: 80/80 PASS).
 */
#include <stdint.h>
#include <string.h>

extern int FUN_00025b78(const void *packet, uint32_t length);

int send_touch_click_event(uint32_t event)
{
    uint8_t packet[64];

    *(uint32_t *)packet = 0;
    memset(packet + 4, 0, 60);
    packet[0] = 1;
    packet[1] = (uint8_t)event;

    return FUN_00025b78(packet, 4);
}
