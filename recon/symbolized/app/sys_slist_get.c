#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00081bac @ 0x00081bac
 * public-name: sys_slist_get
 * durable-map: recon/catalogs/function_names_app.json
 */
/* sys_slist_get @ 0x00081bac; raw FUN_00081bac */

struct slist_node {
    struct slist_node *next;
};

struct slist {
    struct slist_node *head;
    struct slist_node *tail;
};

struct slist_node *sys_slist_get(struct slist *list)
{
    struct slist_node *node = list->head;

    if (node) {
        list->head = node->next;
        if (node == list->tail) {
            list->tail = node->next;
        }
    }
    return node;
}
