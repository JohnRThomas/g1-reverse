/* Reconstructed FUN_00024e60 @ 0x00024e60, extent 0xa0.
 * Readable identity: packet_transport_write_frame.
 * Raw/address backmap: packet_transport_write_frame <= FUN_00024e60 @ 0x00024e60.
 * CFG_VERIFY_CALL_ARITIES=1,1,4,4,4
 */
#include <stdint.h>

extern uint32_t FUN_00024d50(uint32_t type);
extern int FUN_00024dac(uint32_t cursor);
extern int FUN_000256dc(void *transport, uint32_t offset,
                        const void *data, uint32_t length);

int FUN_00024e60(uint32_t type, uint32_t length, const void *payload)
{
    volatile uint32_t *const state = (volatile uint32_t *)0x20007a14UL;
    void *transport = *(void * volatile *)0x20007a44UL;
    uint8_t header[4];
    uint8_t delimiter = 0xfe;
    uint32_t cursor = FUN_00024d50(type);
    uint32_t header_length = length > 0xfeU ? 4U : 2U;

    if (length > cursor - state[3] - 1U - header_length)
        return -2;
    if (FUN_00024dac(cursor) != 0)
        return -1;

    header[0] = (uint8_t)type;
    if (length > 0xfeU) {
        header[1] = 0xffU;
        header[2] = (uint8_t)(length >> 8);
        header[3] = (uint8_t)length;
    } else {
        header[1] = (uint8_t)length;
    }

    cursor = state[3];
    if (FUN_000256dc(transport, cursor, header, header_length) != 0)
        return -1;
    cursor += header_length;
    if (FUN_000256dc(transport, cursor, payload, length) != 0)
        return -1;
    return FUN_000256dc(transport, cursor + length, &delimiter, 1U) != 0 ? -1 : 0;
}
