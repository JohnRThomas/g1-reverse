#include "g1_app_symbols.h"
/* named: l2cap_accept */
/* Reconstructed l2cap_accept @ 0x57468  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern uint32_t l2cap_accept_no_ctx(void);

uint32_t l2cap_accept(uint32_t param_1, int *param_2)
{
    volatile uint32_t *p = (volatile uint32_t *)((uintptr_t)&g_l2cap_fixed_chan_ctx) /*=0x20006210*/;
    if (p[0] != 0) {
        return l2cap_accept_no_ctx();
    }
    p[1] = ((uintptr_t)&tbl_8b264) /*=0x8b264*/;
    *param_2 = (int)(uintptr_t)p;
    return 0;
}

