#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0100ec88 @ 0x0100ec88
 * public-name: controller_packet_build_next
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 *   controller_packet_build_next             <= FUN_0100ec88 @ 0x0100ec88
 *   controller_packet_payload_extract        <= FUN_01026c94 @ 0x01026c94
 * address symbols (name @ address):
 *   g_21000054                               @ 0x21000054
 *   g_21000058                               @ 0x21000058
 *   g_2100005c                               @ 0x2100005c
 *   g_net_ble_conn_create_ctx                @ 0x21000eac
 *   g_net_pending_work_list                  @ 0x21000ec8
 */
/* net-core controller_packet_build_next @ 0x0100ec88
 * Back-map: FUN_0100ec88.  Dequeues one controller work node and either
 * emits the next packet into `packet` or returns after a deferred transition.
 */
#include <stdint.h>
#include <cmsis_gcc.h>

extern void sdc_assertion_fail(uint32_t domain, uint32_t reason)
    __attribute__((noreturn));
extern int FUN_01009d64(uint16_t handle, uint8_t pool);
extern uintptr_t FUN_0100a17c(uint16_t handle);
extern int FUN_01018c58(void);
extern int FUN_0101b74c(void);
extern void controller_packet_payload_extract(uintptr_t owner, uintptr_t replacement);

struct controller_work_node {
    struct controller_work_node *next;             /* +0x00 */
    uintptr_t context_or_callback;                 /* +0x04 */
    volatile uint8_t state;                        /* +0x08 */
    uint8_t inline_payload[4];                     /* +0x09 */
} __attribute__((packed));

struct controller_work_queue {
    uint8_t channel;
    uint8_t reserved_01[3];
    struct controller_work_node **tail_link;       /* +0x04 */
    struct controller_work_node *head;             /* +0x08 */
    uint8_t reserved_0c[8];
    struct controller_work_node *current;          /* +0x14 */
};

typedef void (*node_packet_callback)(struct controller_work_node *, uint8_t *);
typedef uint32_t (*node_packet_result_callback)(struct controller_work_node *,
                                                uint8_t *);
typedef void (*node_callback)(struct controller_work_node *);
typedef void (*context_packet_callback)(uintptr_t, uint8_t *, uint8_t);
typedef void (*handle_packet_callback)(uint16_t, uint8_t *);

enum controller_node_state {
    NODE_AVAILABLE = 0,
    NODE_SENTINEL = 1,
    NODE_PACKET_CALLBACK = 2,
    NODE_PACKET_RESULT = 3,
    NODE_CALLBACK_ONLY = 4,
    NODE_PROCESSING = 5,
    NODE_RADIO_PACKET = 6,
    NODE_CONTEXT_7 = 7,
    NODE_HANDLE_PACKET = 8,
    NODE_CONTEXT_9 = 9,
    NODE_RELEASE_10 = 10,
    NODE_RELEASE_11 = 11,
    NODE_CONTEXT_12 = 12,
    NODE_CONTEXT_COMPLETE = 13,
    NODE_CONTEXT_14 = 14,
    NODE_INLINE_PACKET = 15,
    NODE_HANDLE_CALLBACK = 16,
};

enum packet_build_result {
    PACKET_BUILD_NONE = 0,
    PACKET_BUILD_HANDLE = 2,
    PACKET_BUILD_PACKET = 4,
};

uint32_t controller_packet_build_next(uint8_t *packet)
{
    volatile struct controller_work_queue *const queue =
        (volatile struct controller_work_queue *)((unsigned long)&g_net_pending_work_list) /*=0x21000ec8*/;
    volatile uint8_t *const flow_state = (volatile uint8_t *)((unsigned long)&g_net_ble_conn_create_ctx) /*=0x21000eac*/;
    context_packet_callback *const context_callback =
        (context_packet_callback *)((unsigned long)&g_21000058) /*=0x21000058*/;
    context_packet_callback *const release_callback =
        (context_packet_callback *)((unsigned long)&g_2100005c) /*=0x2100005c*/;
    handle_packet_callback *const handle_callback =
        (handle_packet_callback *)((unsigned long)&g_21000054) /*=0x21000054*/;
    struct controller_work_node *node;
    uint32_t result;
    uint32_t saved_primask;
    uint8_t state;

restart:
    if ((queue->head->state == NODE_HANDLE_CALLBACK) &&
        (flow_state[0x17] != 0) &&
        (*(volatile uint16_t *)(flow_state + 0x18) == 0)) {
        return PACKET_BUILD_NONE;
    }

select_node:
    node = queue->current;
    if ((node != 0) && (node->state != NODE_AVAILABLE)) {
        goto dispatch;
    }

    node = queue->head;
    if (node->state == NODE_SENTINEL) {
        return PACKET_BUILD_NONE;
    }

    saved_primask = __get_PRIMASK();
    __disable_irq();
    queue->head = node->next;
    if (saved_primask == 0) {
        __enable_irq();
    }
    if (node->state == NODE_AVAILABLE) {
        goto select_node;
    }
    queue->current = node;

dispatch:
    state = node->state;
    node->state = NODE_PROCESSING;

    switch (state) {
    case NODE_PACKET_CALLBACK: {
        node_packet_callback callback =
            (node_packet_callback)node->context_or_callback;
        if (callback == 0) {
            sdc_assertion_fail(0x10, 0x1c0);
        }
        callback(node, packet);
        result = PACKET_BUILD_PACKET;
        goto finalize;
    }

    case NODE_PACKET_RESULT: {
        node_packet_result_callback callback =
            (node_packet_result_callback)node->context_or_callback;
        uint32_t callback_result;
        if (callback == 0) {
            sdc_assertion_fail(0x10, 0x1c9);
        }
        callback_result = callback(node, packet);
        result = callback_result & 0xff;
        if (((callback_result >> 8) & 0xff) != 1) {
            goto finalize;
        }
        node->state = NODE_PACKET_RESULT;
        if (result != 0) {
            return result;
        }
        goto restart;
    }

    case NODE_CALLBACK_ONLY: {
        node_callback callback = (node_callback)node->context_or_callback;
        if (callback == 0) {
            sdc_assertion_fail(0x10, 0x1d3);
        }
        callback(node);
        result = PACKET_BUILD_NONE;
        goto finalize;
    }

    case NODE_RADIO_PACKET: {
        node_packet_callback callback =
            (node_packet_callback)node->context_or_callback;
        if (callback == 0) {
            sdc_assertion_fail(0x10, 0x20e);
        }
        callback(node, packet);
        if ((FUN_0101b74c() != 0) || (FUN_01018c58() != 0)) {
            queue->current = 0;
            return PACKET_BUILD_PACKET;
        }
        result = PACKET_BUILD_NONE;
        goto finalize;
    }

    case NODE_CONTEXT_7:
    case NODE_CONTEXT_9:
    case NODE_CONTEXT_12:
    case NODE_CONTEXT_COMPLETE:
    case NODE_CONTEXT_14:
        if (*context_callback == 0) {
            result = PACKET_BUILD_NONE;
            goto finalize;
        }
        (*context_callback)(node->context_or_callback, packet, state);
        if (state == NODE_CONTEXT_COMPLETE) {
            queue->current = 0;
            return PACKET_BUILD_PACKET;
        }
        result = PACKET_BUILD_PACKET;
        goto finalize;

    case NODE_HANDLE_PACKET: {
        uintptr_t context = node->context_or_callback;
        uint16_t handle;
        uintptr_t owner;
        if (context == 0) {
            sdc_assertion_fail(0x10, 0xe3);
        }
        handle = *(volatile uint16_t *)context;
        owner = FUN_0100a17c(handle);
        if (owner == 0) {
            sdc_assertion_fail(0x10, 0xc5);
        }
        *(volatile uint16_t *)(packet + 3) = handle;
        *(volatile uint8_t *)(packet + 0) = 0x0d;
        *(volatile uint8_t *)(packet + 6) = 0;
        *(volatile uint8_t *)(packet + 5) = 1;
        *(volatile uint8_t *)(packet + 2) = 1;
        controller_packet_payload_extract(owner, 0);
        queue->current = 0;
        return PACKET_BUILD_PACKET;
    }

    case NODE_RELEASE_10:
    case NODE_RELEASE_11:
        if (*release_callback == 0) {
            result = PACKET_BUILD_NONE;
            goto finalize;
        }
        {
            uintptr_t context = node->context_or_callback;
            uint8_t packet_kind;
            (*release_callback)(context, packet, state);
            packet_kind = packet[0];
            if ((packet_kind == 0x1d) ||
                ((packet_kind == 0x1a) && (packet[2] != 0))) {
                if (FUN_01009d64(*(volatile uint16_t *)(context + 8), 4) != 0) {
                    sdc_assertion_fail(0x10, 0x1e8);
                }
                queue->current = 0;
                return PACKET_BUILD_PACKET;
            }
        }
        result = PACKET_BUILD_PACKET;
        goto finalize;

    case NODE_INLINE_PACKET:
        *(volatile uint8_t *)(packet + 0) = 0x1e;
        *(volatile uint32_t *)(packet + 3) =
            *(volatile uint32_t *)node->inline_payload;
        result = PACKET_BUILD_PACKET;
        goto finalize;

    case NODE_HANDLE_CALLBACK:
        if (*handle_callback != 0) {
            uintptr_t context = node->context_or_callback;
            if (context == 0) {
                sdc_assertion_fail(0x10, 0x23d);
            }
            (*handle_callback)(*(volatile uint16_t *)context, packet);
        }
        queue->current = 0;
        return PACKET_BUILD_HANDLE;

    default:
        sdc_assertion_fail(0x10, 0x247);
    }

finalize:
    saved_primask = __get_PRIMASK();
    __disable_irq();
    state = node->state;
    if ((state != NODE_PROCESSING) && (state != NODE_AVAILABLE)) {
        if (saved_primask == 0) {
            __enable_irq();
        }
        goto restart;
    }
    node->state = NODE_AVAILABLE;
    queue->current = 0;
    if (saved_primask == 0) {
        __enable_irq();
    }
    if (result != PACKET_BUILD_NONE) {
        return result;
    }
    goto restart;
}
