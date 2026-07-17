/* Reconstructed display_close @ 0x497b0. */

#include <stdint.h>

struct display_close_packet {
    uint8_t type;
    uint8_t reserved;
    uint16_t payload_length;
    uint8_t payload[20];
};

extern void DEBUG_PRINT(uint32_t format, uint32_t name, ...);
extern void FUN_00019c70(uint32_t format, uint32_t name, ...);
extern int FUN_000720d0(void *owner, const void *packet,
                        int option_a, int option_b);
extern void FUN_00086c04(void *destination, const void *source,
                         unsigned int length);
extern void FUN_00086c78(void *destination, int value,
                         unsigned int length);

int display_close(const void *payload, unsigned int payload_length)
{
    struct display_close_packet packet;
    int result;

    FUN_00086c78(&packet, 0, sizeof(packet));
    if (payload_length > 10) {
        if (*(volatile int *)0x2000230cUL > 0) {
            if (*(volatile int *)0x20007554UL == 0) {
                DEBUG_PRINT(0x000ef01cUL, 0x000f018cUL, 10);
            } else {
                FUN_00019c70(0x000ef01cUL, 0x000f018cUL, 10);
            }
        }
        return -1;
    }

    packet.type = 3;
    if (payload != 0) {
        FUN_00086c04(packet.payload, payload, payload_length);
        packet.payload_length = (uint16_t)payload_length;
    }

    result = FUN_000720d0((void *)0x200038c4UL, &packet, 0, 0);
    if (result != 0) {
        DEBUG_PRINT(0x000ef058UL, 0x000f018cUL);
        return -1;
    }

    if (*(volatile int *)0x2000230cUL > 0) {
        if (*(volatile int *)0x20007554UL == 0) {
            DEBUG_PRINT(0x000f0044UL, 0x000f018cUL);
        } else {
            FUN_00019c70(0x000f0044UL, 0x000f018cUL);
        }
    }
    return 0;
}
