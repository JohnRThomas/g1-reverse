#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0100f110 @ 0x0100f110
 * public-name: FUN_0100f110
 * durable-map: recon/catalogs/function_names_net.json
 */
/* CPUNET connection timing snapshot copier @ 0x0100f110.
 * Raw back-map: FUN_0100f110@0x0100f110; true executable extent 0x88. */
#include <stdint.h>

enum { CONTROLLER_MIN_EVENT_TIME = 0x0a90 };

void FUN_0100f110(volatile uint8_t *connection,
                  const volatile uint8_t *timing,
                  const uint8_t *peer_phy, unsigned peer_phy_valid)
{
    uint16_t first_time = *(const uint16_t *)(timing + 4);
    uint16_t second_time = *(const uint16_t *)(timing + 8);

    if ((connection[0x6e] & 0x0c) != 0) {
        if (first_time < CONTROLLER_MIN_EVENT_TIME)
            first_time = CONTROLLER_MIN_EVENT_TIME;
        if ((connection[0x6f] & 0x0c) != 0) {
            if (second_time < CONTROLLER_MIN_EVENT_TIME)
                second_time = CONTROLLER_MIN_EVENT_TIME;
        } else if (peer_phy_valid && (peer_phy[1] & 0x0c) != 0) {
            if (second_time < CONTROLLER_MIN_EVENT_TIME)
                second_time = CONTROLLER_MIN_EVENT_TIME;
        }
    } else if (peer_phy_valid) {
        if ((peer_phy[0] & 0x0c) != 0 &&
            first_time < CONTROLLER_MIN_EVENT_TIME)
            first_time = CONTROLLER_MIN_EVENT_TIME;
        if (((connection[0x6f] & 0x0c) != 0 ||
             (peer_phy[1] & 0x0c) != 0) &&
            second_time < CONTROLLER_MIN_EVENT_TIME)
            second_time = CONTROLLER_MIN_EVENT_TIME;
    } else if ((connection[0x6f] & 0x0c) != 0 &&
               second_time < CONTROLLER_MIN_EVENT_TIME) {
        second_time = CONTROLLER_MIN_EVENT_TIME;
    }

    *(volatile uint16_t *)(connection + 0x4e) = first_time;
    *(volatile uint16_t *)(connection + 0x4c) =
        *(const volatile uint16_t *)(timing + 2);
    *(volatile uint16_t *)(connection + 0x50) =
        *(const volatile uint16_t *)(timing + 6);
    *(volatile uint16_t *)(connection + 0x52) = second_time;
}
