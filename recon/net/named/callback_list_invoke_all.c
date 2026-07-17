/* readable reconstruction; identity: FUN_010294c2 @ 0x010294c2
 * public-name: callback_list_invoke_all
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   callback_list_invoke_all                 <= FUN_010294c2 @ 0x010294c2
 */
/* net-core FUN_010294c2 @ 0x10294c2  (CFG-directed candidate) */
#include <stdint.h>
typedef struct callback_node {
    void (*callback)(void);
    struct callback_node *next;
} callback_node_t;
void callback_list_invoke_all(callback_node_t *node)
{
    while (node != 0) {
        node->callback();
        node = node->next;
    }
}
