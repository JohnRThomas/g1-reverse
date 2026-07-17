#include "g1_net_symbols.h"
/* net-core FUN_0101ddc0 @ 0x101ddc0 */
#include <stdint.h>

struct range_node {
    uint8_t reserved[12];
    uint32_t lower_bound;
    uint8_t reserved2[8];
    struct range_node *next;
};

struct range_node *FUN_0101ddc0(uint32_t value, int require_match)
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
