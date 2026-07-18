/* readable reconstruction; identity: FUN_00082ab8 @ 0x00082ab8
 * public-name: sys_slist_find_and_remove_0
 * durable-map: recon/catalogs/function_names_app.json
 */
/* sys_slist_find_and_remove_0 @ 0x00082ab8; raw FUN_00082ab8 */

struct node {
    struct node *next;
};

struct slist {
    struct node *head;
    struct node *tail;
};

int sys_slist_find_and_remove_0(struct slist *list, struct node *node)
{
    struct node *previous = 0;
    struct node *current = list->head;

    while (current) {
        if (current == node) {
            if (previous) {
                previous->next = current->next;
            } else {
                list->head = current->next;
            }
            if (list->tail == current) {
                list->tail = previous;
            }
            return 1;
        }
        previous = current;
        current = current->next;
    }
    return 0;
}
