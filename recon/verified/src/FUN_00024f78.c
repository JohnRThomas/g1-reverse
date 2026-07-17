/* Reconstructed FUN_00024f78 @ 0x24f78 */
#include <stdint.h>

extern int FUN_00024f08(void *, uint32_t, uint32_t, uint32_t);
extern int FUN_000256dc(uint32_t, uint32_t, void *, uint32_t);

struct transport_probe_frame {
    uint8_t reserved[7];
    uint8_t command;
    uint32_t header;
    uint16_t reserved_halfword;
    uint16_t swapped_length;
};

int FUN_00024f78(uint32_t inherited_r0, uint32_t inherited_r1,
                 uint32_t inherited_r2, uint32_t inherited_r3)
{
    volatile uint8_t *state = (volatile uint8_t *)0x20007a14u;
    volatile uint32_t *state_words = (volatile uint32_t *)state;
    volatile uint32_t *controller = (volatile uint32_t *)0x20007a44u;
    struct transport_probe_frame frame;

    frame.header = state_words[0];
    state_words[3] = 4;
    if (state[2] == 0) {
        uint16_t length = *(volatile uint16_t *)(state + 6);
        frame.swapped_length = (uint16_t)((length << 8) | (length >> 8));
        state_words[3] = 8;
    }

    int status = (int16_t)FUN_00024f08(&frame.header, inherited_r1, 4,
                                       state[2]);
    if (status != 0)
        return status;

    frame.command = 3;
    status = FUN_000256dc(*controller, state_words[3], &frame.command, 1);
    if (status != 0)
        return -1;

    frame.command = 0;
    status = FUN_000256dc(*controller, state_words[3] + 1,
                          &frame.command, 1);
    (void)inherited_r0;
    (void)inherited_r2;
    (void)inherited_r3;
    return status == 0 ? 0 : -1;
}
