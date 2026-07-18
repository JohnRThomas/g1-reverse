/* readable reconstruction; identity: FUN_01037670 @ 0x01037670
 * public-name: FUN_01037670
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103d3b6                           @ 0x0103d3b6
 *   rodata_103eb0e                           @ 0x0103eb0e
 *   g_zephyr_sched_thread_field              @ 0x21004b40
 */
/* Zephyr z_set_prio @ 0x01037670, exact executable extent 0xe0.
 * Raw/address backmaps:
 *   FUN_01037670@0x01037670
 *   scheduler_lock@0x21004b68
 *   ready_queue_sentinel@0x21004b40
 * The terminal return ends at 0x01037750; literals begin there.
 */
#include <stdbool.h>
#include <stdint.h>
#define z_set_prio FUN_01037670

extern int spin_validate(void *); /* FUN_0103610c */
extern void spin_lock(void *); /* FUN_01036144 */
extern int spin_unlock(void *); /* FUN_01036128 */
extern void ready_remove(void *, void *); /* FUN_0103735c */
extern void update_cache(uint32_t); /* FUN_01036f74 */
extern void assert_print(uint32_t, uint32_t, uint32_t); /* FUN_01039bbe */
extern __attribute__((noreturn)) void
assert_post_action(uint32_t, uint32_t); /* FUN_01039bb0 */

bool z_set_prio(uint8_t *thread, int priority)
{
    void *lock = (void *)0x21004b68u;
    bool ready = false;
    int8_t new_priority = (int8_t)priority;

    if (!spin_validate(lock)) {
        assert_print(0x0103d2a7u, 0x0103d3b6u, 0x72u);
        assert_post_action(0x0103d3b6u, 0x72u);
    }
    spin_lock(lock);

    if ((thread[0x0d] & 0x10u) == 0u &&
        *(uint32_t *)(thread + 0x18) == 0u) {
        uint8_t *sentinel = (uint8_t *)0x21004b40u;
        uint8_t *head;
        uint8_t *tail;
        uint8_t *position;

        thread[0x0d] &= 0x7fu;
        ready_remove(sentinel, thread);
        thread[0x0e] = (uint8_t)new_priority;
        thread[0x0d] |= 0x80u;

        if (thread == (uint8_t *)0x210043a8u) {
            assert_print(0x0103d2a7u, 0x0103eb0eu, 0xc1u);
            assert_post_action(0x0103eb0eu, 0xc1u);
        }

        head = *(uint8_t **)sentinel;
        tail = *(uint8_t **)(sentinel + 4);
        position = head == sentinel ? 0 : head;
        while (position != 0) {
            int8_t queued_priority = (int8_t)position[0x0e];

            if (queued_priority > new_priority) {
                break;
            }
            if (position == tail) {
                position = 0;
                break;
            }
            position = *(uint8_t **)position;
        }

        if (position != 0) {
            uint8_t *previous = *(uint8_t **)(position + 4);
            *(uint8_t **)thread = position;
            *(uint8_t **)(thread + 4) = previous;
            *(uint8_t **)previous = thread;
            *(uint8_t **)(position + 4) = thread;
        } else {
            *(uint8_t **)thread = sentinel;
            *(uint8_t **)(thread + 4) = tail;
            *(uint8_t **)tail = thread;
            *(uint8_t **)(sentinel + 4) = thread;
        }
        update_cache(1);
        ready = true;
    } else {
        thread[0x0e] = (uint8_t)new_priority;
    }

    if (!spin_unlock(lock)) {
        assert_print(0x0103d2a7u, 0x0103d3b6u, 0xf0u);
        assert_post_action(0x0103d3b6u, 0xf0u);
    }
    return ready;
}
