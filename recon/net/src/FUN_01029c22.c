/* sdc_slist_pop_and_clear @ 0x01029c22; raw FUN_01029c22
 * Private unpublished SDC-local identity; readable name describes behavior.
 */
#include <stdint.h>

#define sdc_slist_pop_and_clear FUN_01029c22

struct sdc_slist_node {
    struct sdc_slist_node *next;
};

struct sdc_slist_node *sdc_slist_pop_and_clear(struct sdc_slist_node **head)
{
    struct sdc_slist_node *node = *head;

    if (node) {
        volatile uint8_t *bytes = (volatile uint8_t *)node;

        *head = node->next;
        bytes[0] = 0;
        bytes[1] = 0;
        bytes[2] = 0;
        bytes[3] = 0;
    }
    return node;
}
