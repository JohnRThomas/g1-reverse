#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01025c44 @ 0x01025c44
 * public-name: FUN_01025c44
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_task_state_struct                  @ 0x21001c88
 */
/* net-core FUN_01025c44 @ 0x01025c44 -- raw backmap retained. */
#include <stdint.h>

extern __attribute__((noreturn)) void FUN_010256dc(uint32_t, uint32_t, ...);
extern void FUN_01025bf8(void);
#define controller_fault FUN_010256dc

typedef uint32_t (*usage_fn_t)(uint32_t);
typedef void (*notify_fn_t)(const void *);

void FUN_01025c44(uint32_t channel, uint32_t value)
{
    volatile uint8_t *state = (volatile uint8_t *)((unsigned long)&g_net_task_state_struct) /*=0x21001c88*/;
    uint8_t notice[4];

    *(uint32_t *)notice = value;
    if (channel > 4)
        controller_fault(0x68, 0x13d);
    FUN_01025bf8();
    state[0] = 1;
    if (state[1] != 2)
        return;

    void **ops = *(void ***)(state + 8);
    uint32_t usage = ((usage_fn_t)ops[3])(channel);
    uint8_t policy;
    if (state[channel * 2u + 0x15u] < usage)
        policy = 1;
    else if (state[0x1e] == 1)
        policy = 1;
    else
        policy = state[channel * 2u + 0x14u];
    notice[0] = policy;
    notice[1] = (uint8_t)channel;
    ((notify_fn_t)ops[0])(notice);
}
