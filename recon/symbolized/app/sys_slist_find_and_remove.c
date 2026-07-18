#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0008137e @ 0x0008137e
 * public-name: sys_slist_find_and_remove
 * durable-map: recon/catalogs/function_names_app.json
 */
/* sys_slist_find_and_remove @ 0x0008137e; raw FUN_0008137e.
 * Zephyr sys_slist_find_and_remove inline instance with bool result. */
struct slist_node { struct slist_node *next; };
struct slist { struct slist_node *head; struct slist_node *tail; };
int sys_slist_find_and_remove(struct slist *list, struct slist_node *node)
{
    struct slist_node *previous = 0;
    struct slist_node *current = list->head;
    while (current != 0) {
        if (current == node) {
            struct slist_node *next = node->next;
            if (previous == 0) {
                list->head = next;
            } else {
                previous->next = next;
            }
            if (list->tail == node) {
                list->tail = previous ? previous : next;
            }
            node->next = 0;
            return 1;
        }
        previous = current;
        current = current->next;
    }
    return 0;
}
