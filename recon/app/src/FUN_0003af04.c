/* Reconstructed FUN_0003af04 @ 0x3af04 (exact 110-byte extent). */
#include <stdint.h>

extern uint8_t *FUN_000167a8(void);
extern uint32_t FUN_00037060(void);
extern uint32_t FUN_000370bc(void);
extern uint32_t FUN_0003719c(void);
extern void FUN_00047b1c(void *packet, uint32_t length);
extern void FUN_00047ba8(void);

void FUN_0003af04(void)
{
    if (*FUN_000167a8() == 2)
        return;

    uint32_t packet_words[4];
    packet_words[0] = 0;
    packet_words[1] = 0;
    packet_words[2] = 0;
    packet_words[3] = 0;
    uint8_t *packet = (uint8_t *)packet_words;
    packet[0] = 0x22;
    packet[1] = 0x08;
    packet[4] = 2;
    uint8_t *state = FUN_000167a8();
    packet[5] = *(uint8_t *)(*(uint32_t *)(state + 0xfec) + 0x64);
    uint8_t mode = *(volatile uint8_t *)0x2000496au;
    packet[6] = mode;

    if (mode == 0)
        packet[7] = (uint8_t)(FUN_00037060() + 1);
    else if (mode == 1)
        packet[7] = (uint8_t)(FUN_000370bc() + 1);
    else if (mode == 2)
        packet[7] = (uint8_t)(FUN_0003719c() + 1);

    FUN_00047b1c(packet, 8);
    FUN_00047ba8();
}
