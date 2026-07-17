/* readable reconstruction; identity: FUN_010294d2 @ 0x010294d2
 * public-name: controller_intrusive_list_append_unique
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   controller_intrusive_list_append_unique  <= FUN_010294d2 @ 0x010294d2
 */
/* net-core FUN_010294d2 @ 0x10294d2  (CFG-directed candidate) */
#include <stdint.h>

struct controller_intrusive_node {
    uint32_t payload;
    struct controller_intrusive_node *next;
};

/* Raw back-map: FUN_010294d2 @ 0x010294d2, exact extent 0x1c bytes. */
void controller_intrusive_list_append_unique(struct controller_intrusive_node **head,
                  struct controller_intrusive_node *node)
{
    struct controller_intrusive_node *cursor = *head;

    if (cursor == 0) {
        *head = node;
        return;
    }
    for (;;) {
        struct controller_intrusive_node *next = cursor->next;
        if (next == 0) {
            if (cursor != node) {
                cursor->next = node;
            }
            return;
        }
        if (cursor == node) {
            return;
        }
        cursor = next;
    }
}
