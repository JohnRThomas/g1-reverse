#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_k_poll_event__param_0739               [param_0739; library]
 * Raw function identity: 0x000867da.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_000867da @ 0x000867da
 * public-name: signal_poll_event
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   signal_poll_event                        <= FUN_000867da @ 0x000867da
 */
/* CPUAPP Zephyr poll signal_poll_event @ 0x000867da.
 * Raw/address back-map: FUN_000867da / 0x000867da.
 */
#include <stdint.h>
extern int z_work_submit_to_queue(void *, void *); /* FUN_00072f28 */
extern void z_ready_thread_locked(void *); /* FUN_000738d4 */
extern void z_unpend_thread(void *); /* FUN_000742b4 */
extern void z_abort_timeout(void *); /* FUN_00074d74 */

struct poll_event_view {
    uint32_t node[2];
    void *poller;
    uint32_t tag : 8;
    uint32_t type : 6;
    uint32_t state : 7;
    uint32_t mode : 1;
    uint32_t unused : 10;
};
#define signal_poll_event signal_poll_event

int signal_poll_event(uint8_t *event, uint32_t state)
{
    uint8_t *poller = *(uint8_t **)(event + 8);
    if (poller != 0) {
        if (poller[1] == 1) {
            uint8_t pending = poller[-0x53] & 2u;
            if (pending != 0) {
                if (*(int32_t *)(poller - 0x34) == -1 &&
                    *(int32_t *)(poller - 0x38) == -2) {
                    poller[0] = 0;
                    return -11;
                }
                z_unpend_thread(poller - 0x60);
                *(int32_t *)(poller + 0x30) = state == 8 ? -4 : 0;
                if ((poller[-0x53] & 0x1fu) == 0 &&
                    *(uint32_t *)(poller - 0x48) == 0) {
                    z_ready_thread_locked(poller - 0x60);
                    poller[0] = 0;
                } else {
                    poller[0] = 0;
                }
            } else {
                poller[0] = 0;
            }
        } else if (poller[1] == 2) {
            if (poller[0] != 0) {
                void *work = *(void **)(poller - 4);
                if (work != 0) {
                    z_abort_timeout(poller + 0x14);
                    *(uint32_t *)(poller + 0x2c) = 0;
                    z_work_submit_to_queue(work, poller - 0x14);
                }
                poller[0] = 0;
            }
        } else {
            poller[0] = 0;
        }
    }
    struct poll_event_view *poll_event = (struct poll_event_view *)event;
    poll_event->poller = 0;
    poll_event->state |= state;
    return 0;
}
