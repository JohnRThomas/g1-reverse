/* CPUAPP framed serial receive/parser @ 0x00033554.
 * Raw/back-map identity: FUN_00033554, exact extent 0x14c bytes. */
#include <stdint.h>

extern void FUN_00086c04(void *destination, const void *source, uint32_t size);
extern void DEBUG_PRINT(uintptr_t format, ...);

uint32_t framed_serial_receive_parser(uint32_t transport, uint8_t **output,
                      uint32_t *output_size)
{
    volatile uint8_t *const received_size = (volatile uint8_t *)0x2001a128u;
    volatile uint8_t *const received = (volatile uint8_t *)0x2001a129u;
    uint32_t offset;

    if (transport == 0u || output == 0 || output_size == 0)
        return 0xffffffffu;
    if (*received_size == 0u)
        return 0xfffffffeu;

    for (offset = 0u; offset <= 0x100u - (uint32_t)*received_size; ++offset) {
        uint32_t payload_size;
        uint32_t index;
        uint8_t checksum;

        if (received[offset] != 0x5au || received[offset + 1u] != 0xa5u ||
            received[offset + 2u] != 0x7fu)
            continue;
        payload_size = received[offset + 3u];
        if ((int32_t)(payload_size + 4u) >= (int32_t)(0x100u - offset))
            continue;

        checksum = 0u;
        for (index = 0u; index != payload_size + 4u; ++index)
            checksum = (uint8_t)(checksum + received[offset + index]);
        if (received[offset + payload_size + 4u] != checksum)
            continue;

        FUN_00086c04(*output, (const void *)(uintptr_t)
                     (0x2001a12du + offset), payload_size);
        *output_size = payload_size;
        DEBUG_PRINT(0x000a7aabu);
        for (index = 0u; index != payload_size; ++index)
            DEBUG_PRINT(0x000a7993u, (uint32_t)(*output)[index]);
        DEBUG_PRINT(0x000f5400u);
        if (offset <= 0x100u - (uint32_t)*received_size) {
            *received_size = 0u;
            return 0u;
        }
        break;
    }

    *received_size = 0u;
    DEBUG_PRINT(0x000a7ac1u);
    return 0xfffffffdu;
}
