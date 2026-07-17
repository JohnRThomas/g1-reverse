#include "g1_net_symbols.h"
/* net-core FUN_010247dc @ 0x10247dc */
#include <stdint.h>

extern int FUN_01024b20(uint32_t channel);
extern void FUN_01024744(void);

void FUN_010247dc(void)
{
    volatile uint8_t *state = (volatile uint8_t *)((unsigned long)&g_154_critical_section_nest_cnt) /*=0x21001bd0*/;
    volatile uint32_t *timer = (volatile uint32_t *)REG_41005000 /*=0x41005000*/;

    if (state[0x1c] != 0)
        return;
    if (FUN_01024b20(*(volatile uint32_t *)(state + 0x20) & 3u) == 0)
        return;

    /* The test-and-set of state[0x0d] is protected with PRIMASK in the image.
     * Final Zephyr wiring must surround it with arch_irq_lock/unlock. */
    if (state[0x0d] != 0)
        return;
    state[0x0d] = 1;

    timer[0x308 / 4] = 0x80;
    timer[0x11c / 4] = 0;
    state[0x24] = 0;
    FUN_01024744();
    timer[0x304 / 4] = 0x80;
}
