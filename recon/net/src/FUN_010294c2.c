/* net-core FUN_010294c2 @ 0x10294c2  (CFG-directed candidate) */
#include <stdint.h>
typedef struct callback_node {
    void (*callback)(void);
    struct callback_node *next;
} callback_node_t;
void FUN_010294c2(callback_node_t *node)
{
    while (node != 0) {
        node->callback();
        node = node->next;
    }
}
