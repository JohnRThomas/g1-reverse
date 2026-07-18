/* net-core FUN_0101dda8 @ 0x0101dda8
 * Readable identity: schedule_node_tail_get.
 */
#include <stdint.h>

uint32_t FUN_0101dda8(void)
{
    uint32_t node = *(volatile uint32_t *)0x2100113cu;

    while (node != 0u) {
        uint32_t next = *(volatile uint32_t *)(uintptr_t)(node + 0x18u);
        if (next == 0u) {
            return node;
        }
        node = next;
    }
    return 0u;
}
