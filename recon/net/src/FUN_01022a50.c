/* FUN_01022a50 @ 0x01022a50: program a radio bit mask and optional descriptor. */
#include <stdint.h>

extern volatile uint32_t *FUN_0102521c(uint32_t index);

static uint32_t channel_bit(uint32_t channel)
{
    return (channel & 0xffu) < 32u ? 1u << (channel & 0xffu) : 0u;
}

void controller_radio_channel_arm(uint32_t channel, uint32_t *descriptor, uint32_t mode)
{
    volatile uint32_t *radio = (volatile uint32_t *)0x4100f000u;
    if (mode == 0u) {
        radio[0x508u / 4u] = channel_bit(channel);
        return;
    }

    uint32_t value = channel | 0x80000000u;
    volatile uint32_t *slot = FUN_0102521c(0u);
    *slot = value;
    *descriptor = value;
    radio[0x504u / 4u] = channel_bit(channel);
}

/* Raw identity/back-map: FUN_01022a50 @ 0x01022a50, true extent 0x30. */
extern __typeof(controller_radio_channel_arm) FUN_01022a50
    __attribute__((alias("controller_radio_channel_arm")));
