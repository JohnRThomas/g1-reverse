/* Reconstructed FUN_0007c28e @ 0x7c28e. */
#include <stdint.h>

extern int FUN_00032ee4(void);
extern void FUN_00022658(uint32_t channel, const void *packet,
                         uint32_t length);

int FUN_0007c28e(const uint8_t *context)
{
    uint8_t packet[32];

    packet[0] = context[0x0fea];
    packet[1] = context[0x0ed5];
    packet[2] = context[0x0ef4];
    packet[3] = context[0x0f60];
    *(uint32_t *)&packet[4] = *(const uint32_t *)&context[0x0f6c];
    packet[8] = context[0x0f98];
    packet[9] = context[0x1070];
    packet[10] = context[0x108d];
    packet[11] = context[0x0ec0];
    *(uint32_t *)&packet[12] = *(const uint32_t *)&context[0x1069];
    *(uint16_t *)&packet[16] = *(const uint16_t *)&context[0x106d];
    packet[18] = context[0x106f];
    packet[19] = context[0x0ef5];
    packet[20] = context[0x108f];
    packet[21] = context[0x1090];
    packet[22] = context[0x1091];
    packet[23] = (uint8_t)FUN_00032ee4();
    packet[24] = context[0x0ec1];
    packet[25] = 0;
    packet[26] = 0;
    packet[27] = 0;
    *(uint32_t *)&packet[28] = *(const uint32_t *)&context[0x0f68];

    FUN_00022658(0x134000, packet, sizeof(packet));
    return 0;
}
