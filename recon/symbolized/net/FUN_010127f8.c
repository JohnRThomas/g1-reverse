#include "g1_net_symbols.h"
/* net-core FUN_010127f8 @ 0x10127f8 */
#include <stdint.h>

#define RADIO_STATE ((volatile uint8_t *)((unsigned long)&g_net_own_addr_info) /*=0x21000f20*/)
#define TX_DESCRIPTOR ((unsigned long)&rodata_1011add) /*=0x1011add*/

extern void FUN_0100ef88(void *, uint32_t, uint32_t, uint32_t);
extern void FUN_010140ec(void *, uint32_t);
extern int FUN_0101f888(void);
extern void FUN_0101fca8(void);
extern void FUN_010208b0(void);

void FUN_010127f8(uint8_t *state)
{
    uint8_t count;

    *(uint16_t *)(state + 0x40) = (uint16_t)(*(uint16_t *)(state + 0x40) + 1);
    if (RADIO_STATE[0x12] != 0) {
        FUN_010208b0();
        FUN_0101fca8();
        RADIO_STATE[0x12] = 0;
    }
    RADIO_STATE[4] = 0;
    if (state[0x79] != 0) {
        FUN_010140ec(state, 1);
        return;
    }
    count = state[0x0d];
    if (count == 0 || *(uint16_t *)(state + 0x40) < count) {
        FUN_010140ec(state, 0);
        return;
    }
    FUN_010140ec(state, 1);
    if ((*(uint16_t *)(state + 2) & 1u) != 0) {
        uint16_t value = **(uint16_t **)(state + 0x1c);
        if (FUN_0101f888() != 0)
            return;
        count = state[0x0d];
        *(uint16_t *)(state + 0xb1) = value;
        state[0xb0] = state[0];
        state[0xaf] = 0x43;
    } else {
        if (FUN_0101f888() != 0)
            return;
        count = state[0x0d];
        state[0xb0] = state[0];
        state[0xb1] = 0xff;
        state[0xb2] = 0xff;
        state[0xaf] = 0x43;
    }
    if (count != 0)
        count = state[0x40];
    state[0xb3] = count;
    FUN_0100ef88(state + 0xa6, TX_DESCRIPTOR, 2, count);
}
