#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0101ddc0 @ 0x0101ddc0
 * public-name: schedule_node_find_at_or_after
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   schedule_node_find_at_or_after           <= FUN_0101ddc0 @ 0x0101ddc0
 * address symbols (name @ address):
 *   g_timeout_list                           @ 0x2100113c
 */
/* net-core FUN_0101ddc0 @ 0x101ddc0 */
#include <stdint.h>

struct range_node {
    uint8_t reserved[12];
    uint32_t lower_bound;
    uint8_t reserved2[8];
    struct range_node *next;
};

struct range_node *schedule_node_find_at_or_after(uint32_t value, int require_match)
{
    struct range_node *node = *(struct range_node *volatile *)((unsigned long)&g_timeout_list) /*=0x2100113c*/;
    struct range_node *best = 0;
    struct range_node *last = node;
    uint32_t best_bound = UINT32_MAX;

    while (node != 0) {
        last = node;
        if (value <= node->lower_bound && node->lower_bound < best_bound) {
            best = node;
            best_bound = node->lower_bound;
        }
        node = node->next;
    }
    if (!require_match && best == 0)
        best = last;
    return best;
}
