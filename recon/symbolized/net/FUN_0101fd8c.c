#include "g1_net_symbols.h"
/* Reconstructed internal net function FUN_0101fd8c @ 0x0101fd8c.
 * Reachable code is [0x0101fd8c,0x0101fdb8), 44 bytes.  Its two-word
 * literal pool occupies [0x0101fdb8,0x0101fdc0). */
#include <stdint.h>
unsigned FUN_0101fd8c(void)
{
    volatile uint8_t *state=(volatile uint8_t *)((unsigned long)&g_net_ccm_op_status) /*=0x210014d8*/;
    volatile uint32_t *radio=(volatile uint32_t *)REG_4100e000 /*=0x4100e000*/;
    if(state[0]==0) return state[2];
    if(radio[0x100/4]!=0 && radio[0x104/4]!=0 && radio[0x108/4]==0)
        return radio[0x400/4]&0xffu;
    return 0x10;
}
