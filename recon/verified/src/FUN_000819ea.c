/* Full reconstruction of FUN_000819ea @ 0x000819ea (100 bytes). */
#include <stdint.h>

struct listener;

struct listener_ops {
    uint32_t reserved[2];
    void (*notify)(struct listener *listener, int forced);
};

struct listener {
    void *owner;
    const struct listener_ops *ops;
    struct listener *next_link;
    uint32_t reserved;
    uint32_t flags;
};

struct listener_owner {
    uint8_t reserved[0x54];
    struct listener **head_link;
};

extern int FUN_0008199a(struct listener *listener);
extern void FUN_00081788(void *owner, struct listener *listener);
extern void FUN_000817b6(struct listener *listener);

void FUN_000819ea(struct listener_owner *owner, int forced)
{
    struct listener **link = owner->head_link;

    if (link != 0) {
        struct listener *listener = (struct listener *)((uint8_t *)link - 8);
        struct listener *next = *link;

        if (next != 0)
            next = (struct listener *)((uint8_t *)next - 8);

        for (;;) {
            struct listener *saved_next = next;
            uint32_t old_flags = __atomic_fetch_and(&listener->flags,
                                                     ~UINT32_C(4),
                                                     __ATOMIC_ACQ_REL);

            if ((old_flags & 4u) != 0 &&
                (forced != 0 || FUN_0008199a(listener) != 0)) {
                FUN_00081788(listener->owner, listener);
                FUN_000817b6(listener);
            }

            if (listener->ops->notify != 0)
                listener->ops->notify(listener, forced);

            if (saved_next == 0)
                break;

            listener = saved_next;
            next = listener->next_link;
            if (next != 0)
                next = (struct listener *)((uint8_t *)next - 8);
        }
    }
}
