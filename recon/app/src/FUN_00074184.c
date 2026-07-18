/* Reconstructed z_thread_priority_set @ 0x00074184 from Zephyr sched.c.
 * Raw backmap: FUN_00074184@0x00074184. */

#include <stdint.h>
#include <stdbool.h>

extern bool FUN_00074060(void *thread, int32_t priority);
extern void FUN_0008664c(void);
#define z_set_prio FUN_00074060
#define z_reschedule_unlocked FUN_0008664c

void z_thread_priority_set(void *thread, int32_t priority)
{
    bool reschedule_needed = z_set_prio(thread, priority);
    uint8_t *current = *(uint8_t * volatile *)0x2000b450u;
    if (reschedule_needed && current[0x0fu] == 0u) {
        z_reschedule_unlocked();
    }
}
