/* net-core controller_payload_copy_after_nine_byte_header @ 0x0100e06c,
 * exact extent 0x1e.
 * Raw/address backmaps:
 *   FUN_0100e06c@0x0100e06c
 *   memory_copy = FUN_01025998@0x01025998
 *   controller_fatal = FUN_01008d00@0x01008d00
 */
#include <stdint.h>
#define controller_payload_copy_after_nine_byte_header FUN_0100e06c

extern void FUN_01025998(void *destination, uint32_t source, uint32_t length,
                         uint32_t context);
extern __attribute__((noreturn)) void
FUN_01008d00(uint32_t domain, uint32_t line, uint32_t value,
             uint32_t context);
#define memory_copy FUN_01025998
#define controller_fatal FUN_01008d00

void controller_payload_copy_after_nine_byte_header(
    uint8_t *packet, uint32_t source, uint32_t length, uint32_t context)
{
    if (length >= 32u) {
        controller_fatal(0x2au, 0xeeu, length, context);
    }
    memory_copy(packet + 9, source, length, context);
    packet[1] = (uint8_t)(length + 6u);
}
