/* Full reconstruction FUN_00030340 @ 0x00030340 (408-byte exact extent). CFG_VERIFY_CALL_ARITIES=1,2,1,2 */
#include <stdint.h>

extern void *FUN_00076d6c(uint32_t);
extern void FUN_00076d7c(void *);
extern void FUN_00086c04(void *, const void *, uint32_t, uint32_t, uint32_t);
extern int FUN_00030178(uint32_t, uint32_t);
extern void FUN_0003016c(uint32_t);
extern int FUN_000302f8(uint32_t, uint32_t *);

static uint32_t bswap32(uint32_t x)
{
    return __builtin_bswap32(x);
}

int FUN_00030340(uint32_t first, uint32_t second,
                 const uint8_t *payload, uint32_t length)
{
    uint32_t packet_size = (length + 14u) & 0xffffu;
    volatile uint8_t *packet = FUN_00076d6c(packet_size);
    if (!packet) return -1;
    *(uint32_t *)packet = 0x02000008u;
    packet[5] = (uint8_t)(length + 12u);
    packet[4] = (uint8_t)((length + 12u) >> 8);
    uint32_t sum = first + second + length;
    for (uint32_t offset = 0; offset < length; offset += 4)
        sum += bswap32(*(const uint32_t *)(payload + offset));
    uint32_t checksum = -sum;
    packet[6] = checksum >> 24;
    packet[7] = checksum >> 16;
    *(volatile uint16_t *)(packet + 8) = (uint16_t)((checksum << 8) | ((checksum >> 8) & 0xff));
    packet[10] = first; packet[11] = second;
    *(volatile uint16_t *)(packet + 12) = (uint16_t)bswap32(length);
    if (length && payload) FUN_00086c04((void *)(packet + 14), payload, length, bswap32(length), first);

    uintptr_t driver = *(volatile uintptr_t *)0x20007bc0u;
    int attempt = 5, result;
    do result = ((int (*)(void *, uint32_t))*(uintptr_t *)(driver + 4))((void *)packet, packet_size);
    while (result < 0 && attempt-- != -1);
    FUN_00076d7c((void *)packet);
    if (attempt == -1) return -1;
    if (FUN_00030178(0x1c10, 0x20000800u) || FUN_00030178(0x4408, 0x15)) return -1;

    volatile uint8_t *modep = (volatile uint8_t *)0x20019dadu;
    uint32_t index = (*modep - 1u) & 0xffu;
    int response_length = index < 5 ? *(const int8_t *)(0x000a49a0u + index) : 0;
    uint32_t setup = index < 5 ? *(const uint8_t *)(0x000a499bu + index) : 0;
    FUN_0003016c(setup);
    uint32_t status = 0;
    int timeout = *modep == 3 ? 100 : 10;
    for (;;) {
        if (FUN_000302f8(0x4410, &status)) return -1;
        if ((int32_t)(status << 2) < 0) break;
        FUN_0003016c(1);
        if (timeout-- == 0) return -1;
    }
    status = (status & 0xffff0000u) | 0x18u;
    uint32_t response_size = (uint32_t)(response_length + 15);
    uint16_t *response = FUN_00076d6c(response_size);
    if (!response) return -1;
    attempt = 5;
    while ((result = ((int (*)(uint32_t *, uint32_t, void *, uint32_t))*(uintptr_t *)driver)
                    (&status, 2, response, response_size)) < 0) {
        if (attempt-- == -1) { FUN_00076d7c(response); return -1; }
    }
    response[0] = __builtin_bswap16(response[0]);
    response[1] = __builtin_bswap16(response[1]);
    response[5] = __builtin_bswap16(response[5]);
    *(uint32_t *)(response + 2) = bswap32(*(uint32_t *)(response + 2));
    if ((uint8_t)response[4] != first || *((uint8_t *)response + 9) != second ||
        *(uint32_t *)(response + 6) != 0) return -1;
    FUN_00076d7c(response);
    return 0;
}
