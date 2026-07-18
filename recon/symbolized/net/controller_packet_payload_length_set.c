#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0100e8f8 @ 0x0100e8f8
 * public-name: controller_packet_payload_length_set
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 *   controller_packet_payload_length_set     <= FUN_0100e8f8 @ 0x0100e8f8
 */
/* net-core controller_packet_payload_length_set @ 0x0100e8f8,
 * exact extent 0x14.
 * Raw/address backmaps:
 *   FUN_0100e8f8@0x0100e8f8
 *   controller_fatal = FUN_01008d00@0x01008d00
 */
#include <stdint.h>
#define controller_packet_payload_length_set controller_packet_payload_length_set

extern __attribute__((noreturn)) void
sdc_assertion_fail(uint32_t domain, uint32_t line, uint32_t value,
             uint32_t context);
#define controller_fatal sdc_assertion_fail

void controller_packet_payload_length_set(
    uint8_t *packet, uint32_t length, uint32_t value, uint32_t context)
{
    if (length >= 252u) {
        controller_fatal(0x2au, 0x6a1u, value, context);
    }
    packet[1] = (uint8_t)length;
}
