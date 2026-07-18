#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01037f8c @ 0x01037f8c
 * public-name: FUN_01037f8c
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   assert_post_action                       <= FUN_01039bb0 @ 0x01039bb0
 *   assert_print                             <= FUN_01039bbe @ 0x01039bbe
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103d3b6                           @ 0x0103d3b6
 *   rodata_103eb5b                           @ 0x0103eb5b
 *   g_net_kernel_timeout_dlist_head          @ 0x21000750
 *   g_net_kernel_curr_tick                   @ 0x210044f0
 */
/* net-core FUN_01037f8c @ 0x1037f8c */
#include <stdint.h>

struct timeout_node {
    struct timeout_node *next;
    struct timeout_node *prev;
    void *handler;
    uint32_t reserved;
    uint64_t ticks;
};

extern int FUN_0103610c(void *lock);
extern void FUN_01036144(void *lock);
extern int FUN_01036128(void *lock);
extern uint32_t FUN_01037f00(void);
extern uint32_t FUN_01037f14(void);
extern void FUN_0103175c(uint32_t event, int flags);
extern void assert_print(const void *module, const void *file, unsigned line);
extern void assert_post_action(const void *file, unsigned line);

void FUN_01037f8c(struct timeout_node *node, void *handler,
                  uint32_t ticks_low, int32_t ticks_high)
{
    /* Queue mutation is enclosed by BASEPRI masking in the original image. */
    void *const lock = (void *)0x21004b70u;
    struct timeout_node *const queue = (struct timeout_node *)((unsigned long)&g_net_kernel_timeout_dlist_head) /*=0x21000750*/;
    uint64_t requested = ((uint64_t)(uint32_t)ticks_high << 32) | ticks_low;
    struct timeout_node *position;
    uint64_t delay;

    if (requested == UINT64_MAX)
        return;
    if (node->next != 0) {
        assert_print((const void *)((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/,
                     (const void *)((unsigned long)&rodata_103eb5b) /*=0x103eb5b*/, 0x6e);
        assert_post_action((const void *)((unsigned long)&rodata_103eb5b) /*=0x103eb5b*/, 0x6e);
        return;
    }

    node->handler = handler;
    if (FUN_0103610c(lock) == 0) {
        assert_print((const void *)((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/,
                     (const void *)((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/, 0x72);
        assert_post_action((const void *)((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/, 0x72);
        return;
    }
    FUN_01036144(lock);

    if ((int64_t)requested >= -1) {
        delay = requested + 1u + FUN_01037f00();
    } else {
        uint64_t uptime = *(volatile uint64_t *)((unsigned long)&g_net_kernel_curr_tick) /*=0x210044f0*/;
        int64_t absolute_delay =
            (int64_t)(UINT64_MAX - UINT64_C(1) - uptime - requested);
        delay = absolute_delay < 1 ? 1u : (uint64_t)absolute_delay;
    }
    node->ticks = delay;

    position = queue->next == queue ? 0 : queue->next;
    while (position != 0) {
        if ((int64_t)node->ticks < (int64_t)position->ticks) {
            position->ticks -= node->ticks;
            node->next = position;
            node->prev = position->prev;
            position->prev->next = node;
            position->prev = node;
            goto inserted;
        }
        node->ticks -= position->ticks;
        if (position == queue->prev)
            break;
        position = position->next;
    }

    node->next = queue;
    node->prev = queue->prev;
    queue->prev->next = node;
    queue->prev = node;

inserted:
    if (queue->next != queue && queue->next == node)
        FUN_0103175c(FUN_01037f14(), 0);

    if (FUN_01036128(lock) == 0) {
        assert_print((const void *)((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/,
                     (const void *)((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/, 0xf0);
        assert_post_action((const void *)((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/, 0xf0);
    }
}
