/* named: l2cap_accept */
/* Reconstructed l2cap_accept @ 0x57468  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern uint32_t l2cap_accept_no_ctx(void);

uint32_t l2cap_accept(uint32_t param_1, int *param_2)
{
    volatile uint32_t *p = (volatile uint32_t *)0x20006210UL;
    if (p[0] != 0) {
        return l2cap_accept_no_ctx();
    }
    p[1] = 0x8b264UL;
    *param_2 = (int)(uintptr_t)p;
    return 0;
}

