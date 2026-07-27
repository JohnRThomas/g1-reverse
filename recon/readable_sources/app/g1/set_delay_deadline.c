#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0002a4d8 @ 0x0002a4d8
 * public-name: set_delay_deadline
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   set_delay_deadline                       <= FUN_0002a4d8 @ 0x0002a4d8
 *   k_uptime_get_1                           <= FUN_0007cb2c @ 0x0007cb2c
 * address symbols (name @ address):
 *   g_delay_deadline_ticks                   @ 0x200040c8
 */
/* Reconstructed FUN_0002a4d8 @ 0x2a4d8  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern unsigned long long k_uptime_get_1(void);

void set_delay_deadline(unsigned int param_1)
{
    uint64_t lVar1 = k_uptime_get_1();
    *(volatile uint64_t *)((unsigned long)&g_delay_deadline_ticks) /*=0x200040c8*/ = lVar1 + (uint64_t)param_1;
}
