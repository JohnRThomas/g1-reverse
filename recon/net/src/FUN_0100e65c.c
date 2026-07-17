/* net-core controller_packet_payload_copy @ 0x0100e65c, exact extent 0x20.
 * Raw/address backmaps:
 *   FUN_0100e65c@0x0100e65c
 *   memory_copy = FUN_01025998@0x01025998
 *   controller_fatal = FUN_01008d00@0x01008d00
 */
#include <stdint.h>
#define controller_packet_payload_copy FUN_0100e65c

extern void FUN_01025998(void *destination, uint32_t source, uint32_t length,
                         uint32_t context);
extern __attribute__((noreturn)) void
FUN_01008d00(uint32_t domain, uint32_t line, uint32_t length,
             uint32_t context);
#define memory_copy FUN_01025998
#define controller_fatal FUN_01008d00

void controller_packet_payload_copy(
    uint8_t *packet, uint32_t source, uint32_t length, uint32_t context)
{
    if (length >= 28u) {
        controller_fatal(0x2au, 0x47eu, length, context);
    }
    packet[1] = (uint8_t)length;
    memory_copy(packet + 3, source, length, context);
}
