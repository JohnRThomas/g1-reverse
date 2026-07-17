/* net-core FUN_0100ef48 @ 0x100ef48  (CFG-directed candidate) */
/* Role: enqueue controller work in state 4. Back-map: FUN_0100ef48. */
#include <stdint.h>
#include <cmsis_gcc.h>

struct controller_work_node {
    struct controller_work_node *next;
    uintptr_t context;
    volatile uint8_t state;
};
struct controller_work_queue {
    uint8_t deferred_event_channel;
    uint8_t reserved[3];
    struct controller_work_node **tail_link;
    struct controller_work_node *head;
};
extern void FUN_0102583c(uint8_t channel);

void FUN_0100ef48(struct controller_work_node *node, uintptr_t context)
{
    volatile struct controller_work_queue *const queue =
        (volatile struct controller_work_queue *)0x21000ec8u;
    struct controller_work_node **link;
    struct controller_work_node *head;
    uint32_t saved_primask;

    if (node->state != 0u) {
        node->state = 4u;
        return;
    }
    node->context = context;
    node->state = 4u;
    saved_primask = __get_PRIMASK();
    __disable_irq();
    link = (struct controller_work_node **)&queue->head;
    node->next = (struct controller_work_node *)&queue->head;
    head = queue->head;
    if ((head == 0) || (head->state != 1u)) {
        link = queue->tail_link;
    }
    *link = node;
    queue->tail_link = &node->next;
    if (saved_primask == 0u) {
        __enable_irq();
    }
    FUN_0102583c(queue->deferred_event_channel);
}
