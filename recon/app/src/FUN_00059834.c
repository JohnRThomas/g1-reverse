/* Full reconstruction FUN_00059834 @ 0x59834, exact extent 230 bytes.
 * 0x5991c is a literal; the next function begins at 0x59920. */
#include <stdint.h>

extern uint64_t FUN_00081de2(void *, void *);
extern void *FUN_000836e8(void *, uint32_t, uint32_t, uint32_t);
extern void FUN_0005833c(void *);
extern void FUN_0005f24c(void *);
extern void FUN_00059730(void *, uint32_t, uint32_t, uint32_t);
extern void FUN_00081e14(void *, uint32_t);
extern void *FUN_0005f148(void *);
extern void FUN_00059708(void *);
extern void FUN_00071cf4(uintptr_t, void *);
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
    uint64_t initial = FUN_00081de2((uint8_t *)owner + 0x30, context + 0x188);
    uint32_t inherited_r1 = (uint32_t)(initial >> 32);
    for (;;) {
        void *item = FUN_000836e8(context + 0x120, inherited_r1, 0, 0);
        if (item == 0) break;
        FUN_0005833c(*(void **)((uint8_t *)item + 0x18));
        FUN_0005f24c(item);
    }
    if (*(uint32_t *)(context + 0x11c) != 0)
        FUN_00059730(context - 8, 0, 0, 0xe);
    *(uint32_t *)(context - 8) = 0;
    FUN_00081e14(context + 0x118, 2);
    if (owner->busy != 0)
        return;
    for (;;) {
        void *item = FUN_0005f148((uint8_t *)owner + 0x28);
        if (item == 0) break;
        FUN_0005833c(*(void **)((uint8_t *)item + 0x18));
        FUN_0005f24c(item);
    }
    for (;;) {
        void *item = FUN_000836e8((uint8_t *)owner + 0x0c, 0, 0, 0);
        if (item == 0) break;
        FUN_0005833c(*(void **)((uint8_t *)item + 0x18));
        FUN_0005f24c(item);
    }
    while (owner->head != 0) {
        struct node_59834 *node = owner->head;
        owner->head = node->next;
        if (owner->tail == node)
            owner->tail = node->next;
        if (node->callback != 0)
            node->callback(owner->connection, 0xe, 0, 0, node->callback_arg);
        FUN_00059708(node);
    }
    owner->connection = 0;
    FUN_00071cf4(0x20003738u, owner);
    FUN_0005c9a4(*(void **)context);
}
