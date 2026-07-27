/* cancel_sync_locked @ 0x00072c98; raw FUN_00072c98 */
#include <stdint.h>

struct cancel_node {
    struct cancel_node *next;
};

struct cancel_list {
    struct cancel_node *head;
    struct cancel_node *tail;
};

struct work_canceller {
    struct cancel_node node;
    void *work;
    uint8_t semaphore[16];
};

extern int z_impl_k_sem_init(unsigned int, unsigned long, unsigned long); /* FUN_00086534 */

int cancel_sync_locked(uint8_t *work, struct work_canceller *canceller)
{
    uint32_t flags = *(uint32_t *)(work + 12);
    int active = (flags >> 1) & 1u;

    if (active) {
        struct cancel_list *pending = (struct cancel_list *)0x2000b478u;

        z_impl_k_sem_init(canceller->semaphore, 0, 1);
        canceller->node.next = 0;
        canceller->work = work;
        if (pending->tail) {
            pending->tail->next = &canceller->node;
        } else {
            pending->head = &canceller->node;
        }
        pending->tail = &canceller->node;
    }
    return active;
}
