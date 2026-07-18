/* sys_slist_find_and_remove_2 @ 0x00081de2; raw FUN_00081de2.
 * Zephyr sys_slist_find_and_remove inline instance with discarded result. */
struct slist_node { struct slist_node *next; };
struct slist { struct slist_node *head; struct slist_node *tail; };
void sys_slist_find_and_remove_2(struct slist *list, struct slist_node *node)
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
            return;
        }
        previous = current;
        current = current->next;
    }
}
