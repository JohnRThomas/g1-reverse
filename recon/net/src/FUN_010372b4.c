/* Zephyr k_sched_unlock @ 0x010372b4, exact executable extent 0x94.
 * Raw/address backmaps:
 *   FUN_010372b4@0x010372b4
 *   scheduler_lock@0x21004b68
 *   current_thread_slot@0x21004b30
 * Its terminal tail branch ends at 0x01037348, where literals begin.
 */
#include <stdint.h>
#include <cmsis_gcc.h>
#define k_sched_unlock FUN_010372b4

extern int spin_validate(void *); /* FUN_0103610c */
extern void spin_lock(void *); /* FUN_01036144 */
extern int spin_unlock(void *); /* FUN_01036128 */
extern void update_cache(uint32_t); /* FUN_01036f74 */
extern void trace_sched_unlock(void); /* FUN_0103b2b4 */
extern void assert_print(uint32_t, uint32_t, uint32_t); /* FUN_01039bbe */
extern __attribute__((noreturn)) void
assert_post_action(uint32_t, uint32_t); /* FUN_01039bb0 */

void k_sched_unlock(void)
{
    void *lock = (void *)0x21004b68u;
    uint8_t *current;

    if (!spin_validate(lock)) {
        assert_print(0x0103d2a7u, 0x0103d3b6u, 0x72u);
        assert_post_action(0x0103d3b6u, 0x72u);
    }
    spin_lock(lock);
    current = *(uint8_t **)0x21004b30u;
    if (current[0x0f] == 0u) {
        assert_print(0x0103d2a7u, 0x0103eb0eu, 0x3f8u);
        assert_post_action(0x0103eb0eu, 0x3f8u);
    }
    if (__get_IPSR() != 0u) {
        assert_print(0x0103d2a7u, 0x0103eb0eu, 0x3f9u);
        assert_post_action(0x0103eb0eu, 0x3f9u);
    }
    ++current[0x0f];
    update_cache(0);
    if (!spin_unlock(lock)) {
        assert_print(0x0103d2a7u, 0x0103d3b6u, 0xf0u);
        assert_post_action(0x0103d3b6u, 0xf0u);
    }
    trace_sched_unlock();
}
