#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0103b53a @ 0x0103b53a
 * public-name: __memcpy_chk
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   __chk_fail                               <= FUN_0102fa84 @ 0x0102fa84
 *   __memcpy_chk                             <= FUN_0103b53a @ 0x0103b53a
 */
/* FUN_0103b53a @ 0x0103b53a: select and copy a non-overlapping span. */
#include <stdint.h>

extern uint64_t __chk_fail(void);
extern void FUN_0103b614(uint32_t destination, uint32_t source,
                         uint32_t length);

void __memcpy_chk(uint32_t low, uint32_t high,
                  uint32_t length, uint32_t limit)
{
    if (length > limit)
        goto acquire_interval;

    for (;;) {
        if (high <= low) {
            if (low < high + length)
                goto acquire_interval;
            if (high != low)
                break;
        }

        if (high >= low + length)
            break;

acquire_interval: {
            uint64_t interval = __chk_fail();
            low = (uint32_t)interval;
            high = (uint32_t)(interval >> 32);
        }
    }

    FUN_0103b614(low, high, length);
}
