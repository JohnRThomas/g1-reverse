/* readable reconstruction; identity: FUN_01025cc8 @ 0x01025cc8
 * public-name: FUN_01025cc8
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_task_state_struct                  @ 0x21001c88
 */
/* net-core FUN_01025cc8 @ 0x1025cc8  (CFG-directed candidate) */
#include <stdint.h>
typedef void (*callback_t)(void);
extern void FUN_01025bf8(void);
void FUN_01025cc8(void) {
    volatile uint8_t *state = (volatile uint8_t *)0x21001c88u;
    uint8_t mode = state[1];
    if (mode == 2 || mode == 3) {
        uintptr_t ops = *(volatile uint32_t *)(state + 8);
        callback_t callback = *(callback_t *)(ops + 8);
        callback();
    }
    state[0x1e] = 0;
    state[0] = 0;
    FUN_01025bf8();
}
