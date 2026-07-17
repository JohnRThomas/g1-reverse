/* readable reconstruction; identity: FUN_0100ef88 @ 0x0100ef88
 * public-name: sdc_work_submit
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_pending_work_list                  @ 0x21000ec8
 */
/* Reconstructed sdc_work_submit @ 0x0100ef88.
 * Back-map: FUN_0100ef88.  Exact extent: 64 bytes including its literal.
 */
#include <stdint.h>
#include <cmsis_gcc.h>

struct controller_work_node {
    struct controller_work_node *next;
    uintptr_t context_or_callback;
    volatile uint8_t state;
};

struct controller_work_queue {
    uint8_t deferred_event_channel;
    uint8_t reserved_01[3];
    struct controller_work_node **tail_link;
    struct controller_work_node *head;
};

extern void controller_work_duplicate_enqueue_assert(void)
    __attribute__((noreturn));
extern void controller_deferred_event_raise(uint8_t channel);

void sdc_work_submit(struct controller_work_node *node,
                     uintptr_t context_or_callback,
                     uint8_t state)
{
    volatile struct controller_work_queue *const queue =
        (volatile struct controller_work_queue *)0x21000ec8u;
    struct controller_work_node **link;
    struct controller_work_node *head;
    uint32_t saved_primask;

    if (node->state != 0) {
        controller_work_duplicate_enqueue_assert();
    }

    node->context_or_callback = context_or_callback;
    node->state = state;
    saved_primask = __get_PRIMASK();
    __disable_irq();
    link = (struct controller_work_node **)&queue->head;
    node->next = (struct controller_work_node *)&queue->head;
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
