#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00074184 @ 0x00074184
 * public-name: z_thread_priority_set
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_reschedule_unlocked                    <= FUN_0008664c @ 0x0008664c
 * address symbols (name @ address):
 *   g_current_thread_ptr                     @ 0x2000b450
 */
/* Reconstructed z_thread_priority_set @ 0x00074184 from Zephyr sched.c.
 * Raw backmap: FUN_00074184@0x00074184. */

#include <stdint.h>
#include <stdbool.h>

extern bool FUN_00074060(void *thread, int32_t priority);
extern void z_reschedule_unlocked(void);
#define z_set_prio FUN_00074060
#define z_reschedule_unlocked z_reschedule_unlocked

void z_thread_priority_set(void *thread, int32_t priority)
{
    bool reschedule_needed = z_set_prio(thread, priority);
    uint8_t *current = *(uint8_t * volatile *)((unsigned long)&g_current_thread_ptr) /*=0x2000b450*/;
    if (reschedule_needed && current[0x0fu] == 0u) {
        z_reschedule_unlocked();
    }
}
