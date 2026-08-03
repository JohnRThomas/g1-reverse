#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0100eec8 @ 0x0100eec8
 * public-name: controller_work_enqueue_packet_result
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_pending_work_list                  @ 0x21000ec8
 */
/* Reconstructed controller_work_enqueue_packet_result @ 0x0100eec8.
 * Back-map: FUN_0100eec8.  Reachable code is [0x0100eec8,0x0100ef04),
 * 60 bytes; 0x0100ef04 is the g_net_pending_work_list literal and
 * 0x0100ef08 begins a separate internal entry.
 */
#include <stdint.h>
#include <cmsis_gcc.h>

struct controller_work_node {
    struct controller_work_node *next;             /* +0x00 */
    uintptr_t context_or_callback;                 /* +0x04 */
    volatile uint8_t state;                        /* +0x08 */
};

struct controller_work_queue {
    uint8_t deferred_event_channel;                /* +0x00 */
    uint8_t reserved_01[3];
    struct controller_work_node **tail_link;       /* +0x04 */
    struct controller_work_node *head;             /* +0x08 */
};

enum controller_work_state {
    CONTROLLER_WORK_AVAILABLE = 0,
    CONTROLLER_WORK_SENTINEL = 1,
    CONTROLLER_WORK_PACKET_RESULT = 3,
};

extern void controller_work_duplicate_enqueue_assert(void)
    __attribute__((noreturn));                     /* FUN_0100ebb8 */
extern void controller_deferred_event_raise(uint8_t channel);
                                                    /* FUN_0102583c */

void controller_work_enqueue_packet_result(
    struct controller_work_node *node,
    uintptr_t packet_result_callback)
{
    volatile struct controller_work_queue *const queue =
        (volatile struct controller_work_queue *)((unsigned long)&g_net_pending_work_list) /*=0x21000ec8*/;
    struct controller_work_node **link;
    struct controller_work_node *head;
    uint32_t saved_primask;

    if (node->state != CONTROLLER_WORK_AVAILABLE) {
        controller_work_duplicate_enqueue_assert();
    }

    node->context_or_callback = packet_result_callback;
    node->state = CONTROLLER_WORK_PACKET_RESULT;

    saved_primask = __get_PRIMASK();
    __disable_irq();

    link = (struct controller_work_node **)&queue->head;
    node->next = (struct controller_work_node *)&queue->head;
    head = queue->head;
    if ((head == 0) || (head->state != CONTROLLER_WORK_SENTINEL)) {
        link = queue->tail_link;
    }
    *link = node;
    queue->tail_link = &node->next;

    if (saved_primask == 0) {
        __enable_irq();
    }
    controller_deferred_event_raise(queue->deferred_event_channel);
}
