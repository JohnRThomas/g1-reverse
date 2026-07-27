/* Reconstructed FUN_00024cc8 @ 0x24cc8 */
#include <stdint.h>

extern void FUN_0007ca24(int, unsigned char *);
extern void FUN_0007c99e(int, unsigned int *);

struct controller_mode_frame {
    uint8_t reserved[11];
    uint8_t mode;
    uint32_t interval[2];
};

uint8_t FUN_00024cc8(uint32_t enable)
{
    struct controller_mode_frame frame;
    volatile uint32_t *controller = (volatile uint32_t *)0x20007a44u;

    frame.mode = 0;
    FUN_0007ca24(*controller, &frame.mode);
    if (frame.mode == 0) {
        if (enable != 0) {
            frame.interval[0] = 0;
            frame.interval[1] = 0;
            FUN_0007c99e(*controller, frame.interval);
        }
    } else if (frame.mode == 1 && enable == 0) {
        frame.interval[0] = 0x12345678u;
        frame.interval[1] = 0x13245678u;
        FUN_0007c99e(*controller, frame.interval);
    }
    FUN_0007ca24(*controller, &frame.mode);
    return frame.mode;
}
