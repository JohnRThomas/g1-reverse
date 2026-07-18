/* readable reconstruction; identity: FUN_01025d0c @ 0x01025d0c
 * public-name: FUN_01025d0c
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_task_state_struct                  @ 0x21001c88
 */
/* net-core FUN_01025d0c @ 0x1025d0c  (CFG-directed candidate) */
/* CPUNET 0x01025d0c, true executable extent 0x18. Raw backmap: FUN_01025d0c. */
#include <stdint.h>

struct mpsl_callback_owner {
    uint8_t reserved[0x18];
    uint32_t (*query)(void);
};
struct mpsl_state {
    uint8_t reserved0;
    uint8_t mode;
    uint8_t reserved1[6];
    struct mpsl_callback_owner *owner;
};

uint32_t FUN_01025d0c(void)
{
    volatile struct mpsl_state *state =
        (volatile struct mpsl_state *)(uintptr_t)0x21001c88u;
    if ((state->mode != 2u) && (state->mode != 3u)) {
        return 0u;
    }
    return state->owner->query();
}
