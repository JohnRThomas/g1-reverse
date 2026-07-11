/* Full reconstruction FUN_00022b00 @ 0x22b00. */
#include <stdint.h>

extern void FUN_00086c78(void *destination, int value, unsigned int size);
extern void FUN_00022658(unsigned int channel, const void *packet,
                         unsigned int size);

static void put_u16(uint8_t *destination, uint16_t value)
{
    destination[0] = (uint8_t)value;
    destination[1] = (uint8_t)(value >> 8);
}

static void put_u32(uint8_t *destination, uint32_t value)
{
    destination[0] = (uint8_t)value;
    destination[1] = (uint8_t)(value >> 8);
    destination[2] = (uint8_t)(value >> 16);
    destination[3] = (uint8_t)(value >> 24);
}

int FUN_00022b00(const uint8_t *state)
{
    uint8_t packet[0x84];
    const volatile uint8_t *identity_a =
        (const volatile uint8_t *)0x20003003u;
    const volatile uint8_t *identity_b =
        (const volatile uint8_t *)0x20002fe3u;
    unsigned int i;

    /* The firmware clears bytes 4..123, then fills the complete 132-byte
     * telemetry record from the application state and two identity blocks. */
    FUN_00086c78(packet + 4, 0, 0x78);
    put_u32(packet + 0, 1);
    packet[8] = state[2];
    put_u32(packet + 12, *(const uint32_t *)(state + 0xf64));
    put_u32(packet + 16, *(const uint32_t *)(state + 0xf94));
    packet[20] = state[0xed4];

    for (i = 0; i < 16; ++i)
        packet[21 + i] = identity_a[i];
    for (i = 0; i < 16; ++i)
        packet[53 + i] = identity_b[i];

    packet[85] = state[3];
    packet[86] = state[4];
    put_u16(packet + 96, *(const uint16_t *)(state + 0x1072));
    put_u16(packet + 98, *(const uint16_t *)(state + 0x1074));
    put_u32(packet + 100, *(const uint32_t *)(state + 0xfa4));
    put_u32(packet + 104, *(const uint32_t *)(state + 0xfa0));
    put_u32(packet + 108, *(const uint32_t *)(state + 0xfa8));
    put_u32(packet + 112, *(const uint32_t *)(state + 0xfac));
    put_u16(packet + 116, *(const uint16_t *)(state + 0xeda));
    put_u16(packet + 118, *(const uint16_t *)(state + 0xedc));
    put_u16(packet + 120, *(const uint16_t *)(state + 0xede));
    put_u32(packet + 124, *(const uint32_t *)(state + 0xfb0));
    put_u32(packet + 128, *(const uint32_t *)(state + 0xfb4));

    FUN_00022658(0x130000, packet, sizeof(packet));
    return 0;
}
