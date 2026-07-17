#include "g1_net_symbols.h"
/* Reconstructed net-core timestamp validator @ 0x01017018. */
#include <stdint.h>

extern int FUN_0101f8d8(void);
extern uint32_t FUN_010202a8(void);
extern uint32_t FUN_0101b15c(void *, uint32_t, uint32_t, void *);

uint32_t FUN_01017018(void *context, const uint8_t stamp[3],
                      uint32_t unused, void *callback_arg)
{
    uint32_t capabilities;
    uint32_t now;
    uint32_t encoded;
    uint32_t scaled;
    uint8_t high = stamp[2];

    (void)unused;
    capabilities = (uint32_t)FUN_0101f8d8();
    if ((capabilities & 4) == 0 && (high & 0xe0) == 0x40)
        return 0;

    capabilities = (uint32_t)FUN_0101f8d8();
    if ((capabilities & 2) == 0 && (high & 0xe0) == 0x20)
        return 0;
    if ((stamp[0] & 0x3f) > 0x24)
        return 0;

    now = FUN_010202a8();
    encoded = stamp[1] | ((uint32_t)(high & 0x1f) << 8);
    scaled = encoded * ((stamp[0] & 0x80) ? 300U : 30U);
    if (scaled - now < 0x10e || now > scaled)
        return 0;

    *(volatile uint8_t *)((unsigned long)&g_2100104c) /*=0x2100104c*/ = high;
    *(volatile uint16_t *)((unsigned long)&g_net_radio_pending_proc_flag) /*=0x2100104a*/ =
        (uint16_t)(stamp[0] | ((uint16_t)stamp[1] << 8));
    return FUN_0101b15c(context, high,
                        (uint16_t)(stamp[0] | ((uint16_t)stamp[1] << 8)),
                        callback_arg);
}
