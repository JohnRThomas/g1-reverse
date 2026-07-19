#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000818dc @ 0x000818dc
 * public-name: att_send_with_retry
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   net_buf_unref                            <= FUN_0005f24c @ 0x0005f24c
 *   k_work_schedule                          <= FUN_00073418 @ 0x00073418
 *   att_send_data_frags                      <= FUN_00081852 @ 0x00081852
 *   att_send_with_retry                      <= FUN_000818dc @ 0x000818dc
 */
/* Reconstructed FUN_000818dc @ 0x818dc  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>

extern void net_buf_unref(uintptr_t);
extern void k_work_schedule(uintptr_t, unsigned, unsigned, unsigned);
extern uint64_t att_send_data_frags(uintptr_t, int *, unsigned);
extern int net_buf_get(uintptr_t, unsigned, unsigned, unsigned);

void att_send_with_retry(uintptr_t owner, unsigned inherited_wait, unsigned unused)
{
    (void)unused;
    int item;
    for (;;) {
        item = *(volatile int *)(owner - 4);
        if (item == 0) {
            item = net_buf_get(owner - 0x20, inherited_wait, 0, 0);
            if (item == 0)
                return;
        } else {
            *(volatile int *)(owner - 4) = 0;
        }

        uint64_t result_pair = att_send_data_frags(
            owner - 0x50, &item,
            **(volatile uint16_t **)(uintptr_t)(item + 0x18));
        int result = (int)(uint32_t)result_pair;
        if (result >= 0)
            continue;
        if (result == -11) {
            *(volatile int *)(owner - 4) = item;
            k_work_schedule(owner, (unsigned)(result_pair >> 32), 0x8000, 0);
            return;
        }
        net_buf_unref((uintptr_t)item);
        return;
    }
}
