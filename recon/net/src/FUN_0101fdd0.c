/* net-core controller_radio_request_configure @ 0x0101fdd0.
 * Raw backmap: FUN_0101fdd0@0x0101fdd0. */
#include <stdint.h>

extern void FUN_01020088(uint32_t);
extern void FUN_01008d00(uint32_t, uint32_t, uint32_t, uint32_t);

void FUN_0101fdd0(uint32_t mode, uint32_t context, uint32_t selector,
                  uint32_t channel, uint8_t power_index)
{
    volatile uint32_t *radio = (volatile uint32_t *)0x4100e000u;
    volatile uint32_t *timer = (volatile uint32_t *)0x4100f000u;
    volatile uint8_t *request = (volatile uint8_t *)0x210014dcu;
    uint32_t timer_value = 0x4100f000u;

    FUN_01020088(1);
    radio[0x141] = (mode & 3u) | (channel << 16) | 0x01000000u;
    radio[0x142] = context;
    radio[0x146] = (radio[0x146] & 0xffffff00u) | selector;
    radio[0x21] = 0;
    request[4] = (uint8_t)channel;
    timer[0x142] = 0x200;

    if ((mode & 0xfbu) == 0) {
        timer_value = 0x80000009u;
        radio[0x60] = timer_value;
        radio[0x21] = timer_value;
    }
    if (power_index > 2u) {
        FUN_01008d00(0x3c, 0x1d7, timer_value, 0x210014dcu);
        return;
    }

    radio[0x148] =
        ((volatile const uint8_t *)0x0103c4ccu)[power_index];
    if (mode == 1u) {
        ((volatile uint32_t *)0x41008000u)[0x74] = 0x80000009u;
        radio[0x23] = 0x80000009u;
        request[1] = 1;
        request[3] = 1;
    } else {
        request[3] = (uint8_t)mode;
        request[1] = 1;
        if (mode > 2u) {
            return;
        }
    }
    request[0] = 1;
    radio[0x40] = 0;
    radio[0x80] = 0;
    radio[0] = 1;
}
