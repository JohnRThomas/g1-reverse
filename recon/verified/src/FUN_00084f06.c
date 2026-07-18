/* Reconstructed linked_node_at_index @ 0x00084f06.
 * Raw/address back-map: FUN_00084f06 / 0x00084f06.
 */
#include <stdint.h>

struct linked_node_raw {
    struct linked_node_raw *next;
};

struct linked_owner_raw {
    uint32_t reserved[2];
    struct linked_node_raw *head;
};

#define linked_node_at_index FUN_00084f06
struct linked_node_raw *linked_node_at_index(struct linked_owner_raw *owner,
                                             uint32_t index)
{
    struct linked_node_raw *node = owner == 0 ? 0 : owner->head;
    while (node != 0 && index != 0u) {
        node = node->next;
        index--;
    }
    return node;
}
