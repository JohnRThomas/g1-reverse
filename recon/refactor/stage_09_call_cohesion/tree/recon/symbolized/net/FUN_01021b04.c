#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01021b04 @ 0x01021b04
 * public-name: FUN_01021b04
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_libc_tz_calc_state                     @ 0x210016f0
 */
/* net-core FUN_01021b04 @ 0x01021b04, exact Thumb extent 0x74 bytes. */
#include <stdint.h>
#include "../../headers/g1_dedupe.h"

extern void FUN_010256dc();
extern void FUN_01025c38(void);
#define controller_fault FUN_010256dc
#define controller_pending_work_raise FUN_01025c38

/* Advance the active bank's record and notify its optional completion hook. */
void FUN_01021b04(void)
{
    volatile uint8_t *const state = (volatile uint8_t *)((unsigned long)&g_libc_tz_calc_state) /*=0x210016f0*/;
    uint8_t bank = state[0x49];
    volatile uint8_t *const bank_slot = state + 0x30u + bank * 3u;
    uint8_t record = bank_slot[0];

    if (record == 0x20u) {
        G1_NORETURN_CALL(controller_fault(0x70u, 0x331u));
    }

    volatile uint8_t *const link =
        state + 0x50u + ((uint32_t)record + (uint32_t)bank * 0x20u) * 2u;
    bank_slot[0] = link[1];
    state[0x39] = 0xffu;
    uint8_t ready = state[0xe8u + (uint32_t)record * 0x20u];
    state[0x4a] = record;
    state[0x38] = 0u;
    state[0x2a] = 0u;
    link[0] = 2u;

    if (ready == 0u) {
        controller_pending_work_raise();
    }

    void (*completion)(uint32_t) =
        *(void (**)(uint32_t))(uintptr_t)(state + 0x4d0);
    if (completion != 0) {
        completion(0u);
    }
}
