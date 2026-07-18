/* CPUNET private controller queue insertion @ 0x0100ef08.
 * True executable extent: [0x0100ef08, 0x0100ef44); literal follows.
 * Raw back-map: FUN_0100ef08@0x0100ef08. */
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

extern void controller_deferred_event_raise(uint8_t channel); /* FUN_0102583c@0x0102583c */

void FUN_0100ef08(struct controller_work_node *node, uintptr_t context)
{
    volatile struct controller_work_queue *const queue =
        (volatile struct controller_work_queue *)0x21000ec8u;
    struct controller_work_node **link;
    struct controller_work_node *head;
    uint32_t key;

    if (node->state != 0u) {
        node->state = 3u;
        return;
    }
    node->context = context;
    node->state = 3u;
    key = __get_PRIMASK();
    __disable_irq();
    node->next = (struct controller_work_node *)&queue->head;
    link = (struct controller_work_node **)&queue->head;
    head = queue->head;
    if (head == 0 || head->state != 1u)
        link = queue->tail_link;
    *link = node;
    queue->tail_link = &node->next;
    if (key == 0u)
        __enable_irq();
    controller_deferred_event_raise(queue->deferred_event_channel);
}
