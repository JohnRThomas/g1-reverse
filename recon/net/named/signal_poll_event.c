/* readable reconstruction; identity: FUN_0103b442 @ 0x0103b442
 * public-name: signal_poll_event
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   signal_poll_event                        <= FUN_0103b442 @ 0x0103b442
 */
/* net-core FUN_0103b442 @ 0x103b442  (CFG-directed candidate) */
#include <stdint.h>
struct poll_event_layout { uint32_t node[2]; uint8_t *poller; uint32_t flags; };
extern void thread_unpend(void *); /* =FUN_01037850 */
extern void thread_ready(void *); /* =FUN_0103705c */
extern void timeout_abort(void *); /* =FUN_010380d8 */
extern void work_submit_to_queue(void *, void *); /* =FUN_01036c2c */
int signal_poll_event(struct poll_event_layout *event, uint32_t state)
{
    uint8_t *poller = event->poller;
    if (poller != 0) {
        if (poller[1] == 1u) {
            uint8_t pending = poller[-0x53] & 2u;
            if (pending != 0u) {
                if (*(int32_t *)(poller - 0x34) == -1 && *(int32_t *)(poller - 0x38) == -2) {
                    poller[0] = 0u; return -11;
                }
                thread_unpend(poller - 0x60);
                *(int32_t *)(poller + 0x30) = state == 8u ? -4 : 0;
                if (((poller[-0x53] & 0x1fu) == 0u) && (*(int32_t *)(poller - 0x48) == 0))
                    thread_ready(poller - 0x60);
                poller[0] = 0u;
            } else poller[0] = 0u;
        } else if (poller[1] == 2u) {
            if (poller[0] != 0u) {
                void *queue = *(void **)(poller - 4);
                if (queue != 0) {
                    timeout_abort(poller + 0x14);
                    *(uint32_t *)(poller + 0x2c) = 0u;
                    work_submit_to_queue(queue, poller - 0x14);
                }
                poller[0] = 0u;
            }
        } else poller[0] = 0u;
    }
    event->poller = 0;
    event->flags |= (state & 0x7fu) << 14;
    return 0;
}
