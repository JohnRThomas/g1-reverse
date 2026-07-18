/* readable reconstruction; identity: FUN_00071b2c @ 0x00071b2c
 * public-name: g1_recon_k_heap_free_validated
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_spin_lock_valid                        <= FUN_00072040 @ 0x00072040
 *   z_spin_unlock_valid                      <= FUN_0007205c @ 0x0007205c
 *   z_spin_lock_set_owner                    <= FUN_00072078 @ 0x00072078
 *   z_reschedule                             <= FUN_000739f0 @ 0x000739f0
 *   z_unpend_all                             <= FUN_00086668 @ 0x00086668
 */
/* Reconstructed g1_recon_k_heap_free_validated @ 0x00071b2c from Zephyr kheap.c.
 * Raw backmap: FUN_00071b2c@0x00071b2c. */

#include <stdint.h>

extern int z_spin_lock_valid(void *lock);
extern void z_spin_lock_set_owner(void *lock);
extern void FUN_0004b214(void *heap, void *memory);
extern int z_unpend_all(void *wait_queue);
extern void z_reschedule(void *lock, uint32_t key);
extern int z_spin_unlock_valid(void *lock);
#define z_spin_lock_valid z_spin_lock_valid
#define z_spin_lock_set_owner z_spin_lock_set_owner
#define sys_heap_free FUN_0004b214
#define z_unpend_all z_unpend_all
#define z_reschedule z_reschedule
#define z_spin_unlock_valid z_spin_unlock_valid

void g1_recon_k_heap_free_validated(void *heap_arg, void *memory)
{
    uint8_t *heap = (uint8_t *)heap_arg;
    void *lock = heap + 0x14u;
    if (z_spin_lock_valid(lock) == 0) {
        return;
    }
    z_spin_lock_set_owner(lock);
    sys_heap_free(heap, memory);
    if (z_unpend_all(heap + 0x0cu) != 0) {
        z_reschedule(lock, 0u);
        return;
    }
    (void)z_spin_unlock_valid(lock);
}
