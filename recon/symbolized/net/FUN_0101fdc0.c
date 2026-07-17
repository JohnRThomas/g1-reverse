#include "g1_net_symbols.h"
/* Reconstructed internal net function FUN_0101fdc0 @ 0x0101fdc0.
 * Code [0x0101fdc0,0x0101fdcc), 12 bytes; one literal at
 * [0x0101fdcc,0x0101fdd0), before FUN_0101fdd0. */
#include <stdint.h>
void FUN_0101fdc0(void)
{
    volatile uint8_t *state=(volatile uint8_t *)((unsigned long)&g_net_radio_pending_reset_flag) /*=0x210014dc*/;
    *(volatile uint16_t *)state=0;
    state[2]=0;
}
