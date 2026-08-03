#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0101de60 @ 0x0101de60
 * public-name: schedule_node_split_insert
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   schedule_node_split_insert               <= FUN_0101de60 @ 0x0101de60
 * address symbols (name @ address):
 *   g_timeout_list                           @ 0x2100113c
 */
/* net-core FUN_0101de60 @ 0x101de60  (CFG-directed candidate) */

#include <stdint.h>
extern __attribute__((noreturn)) void sdc_assertion_fail(uint32_t, uint32_t); /* FUN_01008d00 @ 0x01008d00. */
/* Readable role: schedule_node_split_insert. Raw back-map: FUN_0101de60 @ 0x0101de60. */
void schedule_node_split_insert(void *node_pointer)
{
    uint8_t *node = (uint8_t *)node_pointer;
    uint8_t *split = *(uint8_t **)(node + 0x20);
    uint32_t start = *(uint32_t *)(node + 8);
    if (split != 0 && *(uint32_t *)(split + 8) <= start) {
        uint8_t *previous = *(uint8_t **)(node + 0x18);
        uint8_t *next = *(uint8_t **)(node + 0x1c);
        *(uint8_t **)(split + 0x18) = previous;
        *(uint8_t **)(split + 0x1c) = next;
        if (next == 0)
            *(uint8_t * volatile *)((unsigned long)&g_timeout_list) /*=0x2100113c*/ = split;
        else {
            *(uint8_t **)(next + 0x18) = split;
            previous = *(uint8_t **)(split + 0x18);
        }
        if (previous != 0) {
            *(uint8_t **)(previous + 0x1c) = split;
            *(uint32_t *)(split + 0x0c) =
                (start + *(uint32_t *)(node + 0x0c)) - *(uint32_t *)(split + 8);
        } else {
            *(uint32_t *)(split + 0x0c) = 0;
        }
        return;
    }
    sdc_assertion_fail(0x37u, 0xcdu);
}
