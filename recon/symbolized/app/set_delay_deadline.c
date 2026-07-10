#include "g1_app_symbols.h"
/* named: set_delay_deadline */
/* globals referenced:
//   0x200040c8  g_delay_deadline_ticks       
*/
/* Reconstructed set_delay_deadline @ 0x2a4d8  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern uint64_t k_uptime_get_1(void);

void set_delay_deadline(unsigned int param_1)
{
    uint64_t lVar1 = k_uptime_get_1();
    *(volatile uint64_t *)((uintptr_t)&g_delay_deadline_ticks) /*=0x200040c8*/ = lVar1 + (uint64_t)param_1;
}

