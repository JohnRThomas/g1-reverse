#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00059834 @ 0x00059834
 * public-name: FUN_00059834
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_att_req_free                          <= FUN_00059708 @ 0x00059708
 *   att_handle_rsp                           <= FUN_00059730 @ 0x00059730
 *   net_buf_slist_get                        <= FUN_0005f148 @ 0x0005f148
 *   net_buf_unref                            <= FUN_0005f24c @ 0x0005f24c
 *   k_mem_slab_free                          <= FUN_00071cf4 @ 0x00071cf4
 *   sys_slist_find_and_remove_2              <= FUN_00081de2 @ 0x00081de2
 *   atomic_clear_bit_0                       <= FUN_00081e14 @ 0x00081e14
 *   net_buf_get                              <= FUN_000836e8 @ 0x000836e8
 * address symbols (name @ address):
 *   g_bt_att_slab                            @ 0x20003738
 */
/* Full reconstruction FUN_00059834 @ 0x59834, exact extent 230 bytes.
 * 0x5991c is a literal; the next function begins at 0x59920. */
#include <stdint.h>

extern uint64_t sys_slist_find_and_remove_2(void *, void *);
extern void *net_buf_get(void *, uint32_t, uint32_t, uint32_t);
extern void FUN_0005833c(void *);
extern void net_buf_unref(void *);
extern void att_handle_rsp(void *, uint32_t, uint32_t, uint32_t);
extern void atomic_clear_bit_0(void *, uint32_t);
extern void *net_buf_slist_get(void *);
extern void bt_att_req_free(void *);
extern void k_mem_slab_free(uintptr_t, void *);
extern void FUN_0005c9a4(void *);

struct node_59834 {
    struct node_59834 *next;
    void (*callback)(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t);
    uint8_t pad08[16];
    uint32_t callback_arg;
};
struct owner_59834 {
    uint32_t connection;
    struct node_59834 *head;
    struct node_59834 *tail;
    uint8_t queue0c[28];
    uint8_t queue28[8];
    uint32_t busy;
};

void FUN_00059834(uint8_t *context, uint32_t arg1)
{
    struct owner_59834 *owner = *(struct owner_59834 **)(context - 8);
    (void)arg1;
    if (owner == 0)
        return;
    uint64_t initial = sys_slist_find_and_remove_2((uint8_t *)owner + 0x30, context + 0x188);
    uint32_t inherited_r1 = (uint32_t)(initial >> 32);
    for (;;) {
        void *item = net_buf_get(context + 0x120, inherited_r1, 0, 0);
        if (item == 0) break;
        FUN_0005833c(*(void **)((uint8_t *)item + 0x18));
        net_buf_unref(item);
    }
    if (*(uint32_t *)(context + 0x11c) != 0)
        att_handle_rsp(context - 8, 0, 0, 0xe);
    *(uint32_t *)(context - 8) = 0;
    atomic_clear_bit_0(context + 0x118, 2);
    if (owner->busy != 0)
        return;
    for (;;) {
        void *item = net_buf_slist_get((uint8_t *)owner + 0x28);
        if (item == 0) break;
        FUN_0005833c(*(void **)((uint8_t *)item + 0x18));
        net_buf_unref(item);
    }
    for (;;) {
        void *item = net_buf_get((uint8_t *)owner + 0x0c, 0, 0, 0);
        if (item == 0) break;
        FUN_0005833c(*(void **)((uint8_t *)item + 0x18));
        net_buf_unref(item);
    }
    while (owner->head != 0) {
        struct node_59834 *node = owner->head;
        owner->head = node->next;
        if (owner->tail == node)
            owner->tail = node->next;
        if (node->callback != 0)
            node->callback(owner->connection, 0xe, 0, 0, node->callback_arg);
        bt_att_req_free(node);
    }
    owner->connection = 0;
    k_mem_slab_free(((unsigned long)&g_bt_att_slab) /*=0x20003738*/, owner);
    FUN_0005c9a4(*(void **)context);
}
