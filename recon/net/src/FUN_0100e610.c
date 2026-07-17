/* net-core controller_packet_length_matches_type @ 0x0100e610,
 * exact extent 0x20.
 * Raw/address backmaps:
 *   FUN_0100e610@0x0100e610
 *   expected_packet_lengths@0x0103c190
 */
#include <stdbool.h>
#include <stdint.h>
#define controller_packet_length_matches_type FUN_0100e610

bool controller_packet_length_matches_type(const uint8_t *packet)
{
    uint8_t length = packet[1];
    uint8_t type = packet[3];
    volatile const uint8_t *expected_packet_lengths =
        (volatile const uint8_t *)0x0103c190u;

    if (length == 0u) {
        return false;
    }
    if (type > 0x2au) {
        return true;
    }
    return expected_packet_lengths[type] == length;
}
