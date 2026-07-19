#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00057468 @ 0x00057468
 * public-name: l2cap_accept
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   l2cap_accept_no_ctx                      <= FUN_00057438 @ 0x00057438
 *   l2cap_accept                             <= FUN_00057468 @ 0x00057468
 * address symbols (name @ address):
 *   rodata_8b264                             @ 0x0008b264
 *   g_l2cap_fixed_chan_ctx                   @ 0x20006210
 */
/* Reconstructed FUN_00057468 @ 0x57468  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern uint32_t l2cap_accept_no_ctx(uint32_t);

uint32_t l2cap_accept(uint32_t param_1, int *param_2)
{
    volatile uint32_t *p = (volatile uint32_t *)((unsigned long)&g_l2cap_fixed_chan_ctx) /*=0x20006210*/;
    if (p[0] != 0) {
        return l2cap_accept_no_ctx(param_1);
    }
    p[1] = ((unsigned long)&rodata_8b264) /*=0x8b264*/;
    *param_2 = (int)(uintptr_t)p;
    return 0;
}
