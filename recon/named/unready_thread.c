/* readable reconstruction; identity: FUN_00073e88 @ 0x00073e88
 * public-name: unready_thread
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_current_thread_ptr                     @ 0x2000b450
 *   g_sched_ready_runq                       @ 0x2000b464
 */
/* unready_thread @ 0x00073e88; raw FUN_00073e88 */
#include <stdint.h>

extern void dlist_unlink_node(void *, void *); /* FUN_00073cdc */
extern void update_cache(int); /* FUN_000737d8 */

void unready_thread(uint8_t *thread)
{
    if ((int8_t)thread[0x0d] < 0) {
        thread[0x0d] &= 0x7f;
        dlist_unlink_node((void *)0x2000b464u, thread);
    }
    update_cache(*(void **)0x2000b450u == (void *)thread);
}
