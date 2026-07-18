/* Reconstructed k_heap_free @ 0x00071b2c from Zephyr kheap.c.
 * Raw backmap: FUN_00071b2c@0x00071b2c. */

#include <stdint.h>

extern int FUN_00072040(void *lock);
extern void FUN_00072078(void *lock);
extern void FUN_0004b214(void *heap, void *memory);
extern int FUN_00086668(void *wait_queue);
extern void FUN_000739f0(void *lock, uint32_t key);
extern int FUN_0007205c(void *lock);
#define z_spin_lock_valid FUN_00072040
#define z_spin_lock_set_owner FUN_00072078
#define sys_heap_free FUN_0004b214
#define z_unpend_all FUN_00086668
#define z_reschedule FUN_000739f0
#define z_spin_unlock_valid FUN_0007205c

void FUN_00071b2c(void *heap_arg, void *memory)
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
