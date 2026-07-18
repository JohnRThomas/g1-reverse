#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0103b3e0 @ 0x0103b3e0
 * public-name: FUN_0103b3e0
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0103b3e0 @ 0x103b3e0  (CFG-directed candidate) */
#include <stdint.h>
struct poll_node { struct poll_node *next; struct poll_node *prev; uintptr_t poller; };
extern int scheduler_priority_compare(const void *, const void *); /* =FUN_0103b28a */
static inline void *poller_thread(uintptr_t poller)
{
    return poller != 0u ? (void *)(poller - 0x60u) : (void *)0;
}
static inline void poll_list_insert_before(struct poll_node *position,
                                           struct poll_node *event)
{
    event->next = position;
    event->prev = position->prev;
    position->prev->next = event;
    position->prev = event;
}
void FUN_0103b3e0(struct poll_node *events, struct poll_node *event,
                  uintptr_t poller)
{
    struct poll_node *pending = events->prev;
    if ((events != events->next) && (pending != 0)) {
        if (scheduler_priority_compare(poller_thread(pending->poller),
                                       poller_thread(poller)) <= 0) {
            pending = events->next;
            if (events != pending) {
                while (pending != 0) {
                    if (scheduler_priority_compare(poller_thread(poller),
                                                   poller_thread(pending->poller)) > 0) {
                        poll_list_insert_before(pending, event);
                        return;
                    }
                    if (pending == events->prev)
                        break;
                    pending = pending->next;
                }
            }
        }
    }
    poll_list_insert_before(events, event);
}
