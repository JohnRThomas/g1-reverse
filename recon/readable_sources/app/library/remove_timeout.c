#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_k_timer__param_0414                    [param_0414; library]
 * Raw function identity: 0x00074bbc.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00074bbc @ 0x00074bbc
 * public-name: remove_timeout
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_20002d00                               @ 0x20002d00
 */
/* remove_timeout @ 0x00074bbc; raw FUN_00074bbc.
 * NCS 2.5.1 zephyr/kernel/timeout.c delta-list removal helper. */
#include <stdint.h>
struct timeout_node {
    struct timeout_node *next;
    struct timeout_node **previous_link;
    uint32_t reserved[2];
    uint64_t dticks;
};
void remove_timeout(struct timeout_node *timeout)
{
    struct timeout_node *next = timeout->next;
    struct timeout_node *const list_tail =
        *(struct timeout_node * volatile *)((unsigned long)&g_20002d00) /*=0x20002d00*/; /* timeout_list tail */
    if (timeout != list_tail && next != 0) {
        next->dticks += timeout->dticks;
    }
    struct timeout_node **previous_link = timeout->previous_link;
    *previous_link = next;
    next->previous_link = previous_link;
    timeout->next = 0;
    timeout->previous_link = 0;
}
