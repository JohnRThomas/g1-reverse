#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0101a218 @ 0x0101a218
 * public-name: FUN_0101a218
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_session_state_block                @ 0x210010a0
 */
/* net-core FUN_0101a218 @ 0x0101a218 */
#include <stdint.h>

extern uint64_t controller_time_now(void); /* FUN_01022f08 */
extern uint32_t FUN_01023dec(uint32_t unit);
extern int FUN_01023ea8(uint32_t amount, uint32_t unit);
extern void FUN_01023d38(uint32_t updated_offset);

uint32_t FUN_0101a218(void)
{
    volatile uint32_t * const scheduler = (volatile uint32_t *)((unsigned long)&g_net_session_state_block) /*=0x210010a0*/;
    uint64_t now = controller_time_now();
    uint32_t unit = 1;
    uint32_t available;
    uint32_t amount;

    if (*(volatile uint8_t *)scheduler == 4u) {
        uint32_t required = scheduler[1] * 10u;
        uint32_t remaining = scheduler[6] - scheduler[20];
        unit = remaining >= required ? 1u : 2u;
    }

    available = FUN_01023dec(unit);
    if (available <= 0x75u) {
        return 0;
    }

    if (available == UINT32_MAX) {
        amount = scheduler[15] - scheduler[14];
        if (amount > 5000u) {
            amount = 5000u;
        }
    } else {
        if (scheduler[15] <= scheduler[14] + available) {
            available = scheduler[15] - scheduler[14];
        }
        int64_t until_deadline =
            (int64_t)(*(volatile uint64_t *)(scheduler + 12) + 69u - now);
        if (until_deadline < 1) {
            amount = 0;
        } else if ((uint64_t)available >= (uint64_t)until_deadline) {
            amount = (uint32_t)until_deadline;
            if (amount > 5000u) {
                amount = 5000u;
            }
        } else {
            amount = available > 5000u ? 5000u : available;
        }
    }

    if ((uint32_t)controller_time_now() + (191u - (uint32_t)now) > amount) {
        return 0;
    }
    if (FUN_01023ea8(amount, unit) != 0) {
        return 0;
    }

    scheduler[16] += amount;
    scheduler[14] += amount;
    FUN_01023d38(scheduler[16]);
    return 1;
}
