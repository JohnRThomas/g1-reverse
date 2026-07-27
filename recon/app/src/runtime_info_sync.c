/* Reconstructed runtime_info_sync @ 0x16268 */

#include <stdint.h>

struct __attribute__((packed)) runtime_sync_packet {
    uint16_t marker;
    uint8_t runtime[5];
    uint8_t reserved;
};

extern uint32_t FUN_00025b78(const void *packet, uint32_t length);
extern void DEBUG_PRINT(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);

uint32_t runtime_info_sync(const uint8_t *runtime)
{
    struct runtime_sync_packet packet = {
        .marker = 1,
        .runtime = {runtime[0], runtime[1], runtime[2], runtime[3], runtime[4]},
        .reserved = 0,
    };

    uint32_t result = FUN_00025b78(&packet, sizeof(packet));
    if (*(volatile uint8_t *)0x20002fe0UL != 0) {
        *(volatile uint8_t *)0x20002fe0UL = 0;
        if (*(volatile int32_t *)0x2000230cUL > 1) {
            if (*(volatile uint32_t *)0x20007554UL == 0) {
                DEBUG_PRINT(0x0009957cUL, 0x00099beeUL,
                            runtime[0], runtime[1], runtime[2], result,
                            runtime[3], runtime[4]);
            } else {
                FUN_00019c70(0x0009957cUL, 0x00099beeUL,
                             runtime[0], runtime[1], runtime[2], result,
                             runtime[3], runtime[4]);
            }
        }
    }
    return result;
}
