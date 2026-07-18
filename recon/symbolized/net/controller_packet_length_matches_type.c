#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0100e610 @ 0x0100e610
 * public-name: controller_packet_length_matches_type
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   controller_packet_length_matches_type    <= FUN_0100e610 @ 0x0100e610
 * address symbols (name @ address):
 *   rodata_103c190                           @ 0x0103c190
 */
/* net-core controller_packet_length_matches_type @ 0x0100e610,
 * exact extent 0x20.
 * Raw/address backmaps:
 *   FUN_0100e610@0x0100e610
 *   expected_packet_lengths@0x0103c190
 */
#include <stdbool.h>
#include <stdint.h>
#define controller_packet_length_matches_type controller_packet_length_matches_type

bool controller_packet_length_matches_type(const uint8_t *packet)
{
    uint8_t length = packet[1];
    uint8_t type = packet[3];
    volatile const uint8_t *expected_packet_lengths =
        (volatile const uint8_t *)((unsigned long)&rodata_103c190) /*=0x103c190*/;

    if (length == 0u) {
        return false;
    }
    if (type > 0x2au) {
        return true;
    }
    return expected_packet_lengths[type] == length;
}
