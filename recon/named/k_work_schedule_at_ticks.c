/* readable reconstruction; identity: FUN_000531cc @ 0x000531cc
 * public-name: k_work_schedule_at_ticks
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   k_work_schedule_at_ticks                 <= FUN_000531cc @ 0x000531cc
 *   k_work_schedule_for_queue                <= FUN_0007332c @ 0x0007332c
 * address symbols (name @ address):
 *   g_sys_work_q                             @ 0x20005d38
 */
/* Reconstructed FUN_000531cc @ 0x531cc  owned extent: 0x8 bytes */

#include <stdint.h>
extern int k_work_schedule_for_queue(uint32_t, int);
int k_work_schedule_at_ticks(int param_1){
    return k_work_schedule_for_queue(0x20005d38, param_1);
}
