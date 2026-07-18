#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01035e1c @ 0x01035e1c
 * public-name: FUN_01035e1c
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103d3b6                           @ 0x0103d3b6
 */
/* Zephyr k_heap_free @ 0x01035e1c, exact executable extent 0x78.
 * Raw/address backmaps:
 *   FUN_01035e1c@0x01035e1c
 *   sys_heap_free = FUN_0102c470@0x0102c470
 *   z_unpend_all = FUN_0103b2d0@0x0103b2d0
 *   z_reschedule = FUN_01037130@0x01037130
 * Return is at 0x01035e92; literals begin at 0x01035e94.
 */
#include <stdint.h>
#define k_heap_free FUN_01035e1c

extern int spin_validate(void *); /* FUN_0103610c */
extern void spin_lock(void *); /* FUN_01036144 */
extern int spin_unlock(void *); /* FUN_01036128 */
extern void sys_heap_free(void *, void *); /* FUN_0102c470 */
extern int z_unpend_all(void *); /* FUN_0103b2d0 */
extern void z_reschedule(void *, uint32_t); /* FUN_01037130 */
extern void assert_print(uint32_t, uint32_t, uint32_t); /* FUN_01039bbe */
extern __attribute__((noreturn)) void
assert_post_action(uint32_t, uint32_t); /* FUN_01039bb0 */

void k_heap_free(uint8_t *heap, void *memory)
{
    void *lock = heap + 0x14;

    if (!spin_validate(lock)) {
        assert_print(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/, 0x72u);
        assert_post_action(((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/, 0x72u);
    }
    spin_lock(lock);
    sys_heap_free(heap, memory);

    if (z_unpend_all(heap + 0x0c)) {
        z_reschedule(lock, 0);
        return;
    }
    if (!spin_unlock(lock)) {
        assert_print(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/, 0xf0u);
        assert_post_action(((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/, 0xf0u);
    }
}
