/* net-core FUN_0100efc8 @ 0x100efc8  (CFG-directed candidate) */
#include <stdint.h>
#include <cmsis_gcc.h>

struct controller_work_node_update {
    struct controller_work_node_update *next;
    uintptr_t context_or_callback;
    volatile uint8_t state;
};

struct controller_work_queue_update {
    uint8_t deferred_event_channel;
    uint8_t reserved_01[3];
    struct controller_work_node_update **tail_link;
    struct controller_work_node_update *head;
};

extern void controller_deferred_event_raise(uint8_t channel);

/* Raw back-map: FUN_0100efc8 @ 0x0100efc8, exact extent 0x38 bytes. */
void FUN_0100efc8(struct controller_work_node_update *node,
                  uintptr_t context_or_callback,
                  uint8_t new_state)
{
    volatile struct controller_work_queue_update *const queue =
        (volatile struct controller_work_queue_update *)0x21000ec8u;
    struct controller_work_node_update **link;
    struct controller_work_node_update *head;
    uint32_t saved_primask;

    if (node->state != 0) {
        node->state = new_state;
        return;
    }

    node->context_or_callback = context_or_callback;
    node->state = new_state;
    saved_primask = __get_PRIMASK();
    __disable_irq();

    link = (struct controller_work_node_update **)&queue->head;
    node->next = (struct controller_work_node_update *)&queue->head;
    head = queue->head;
    if ((head == 0) || (head->state != 1)) {
        link = queue->tail_link;
    }
    *link = node;
    queue->tail_link = &node->next;

    if (saved_primask == 0) {
        __enable_irq();
    }
    controller_deferred_event_raise(queue->deferred_event_channel);
}
