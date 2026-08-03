#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01025cf0 @ 0x01025cf0
 * public-name: controller_transition_pending_check
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_task_state_struct                  @ 0x21001c88
 */
/* net-core FUN_01025cf0 @ 0x1025cf0  (CFG-directed candidate) */
#include <stdint.h>
typedef uint32_t (*callback_t)(void);
uint32_t controller_transition_pending_check(void) {
    volatile uint8_t *state = (volatile uint8_t *)((unsigned long)&g_net_task_state_struct) /*=0x21001c88*/;
    uint8_t mode = state[1];
    if (mode != 2 && mode != 3) return 0;
    uintptr_t ops = *(volatile uint32_t *)(state + 8);
    callback_t callback = *(callback_t *)(ops + 0x10);
    return callback();
}
