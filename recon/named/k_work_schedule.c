/* readable reconstruction; identity: FUN_00073418 @ 0x00073418
 * public-name: k_work_schedule
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   k_work_schedule_for_queue                <= FUN_0007332c @ 0x0007332c
 *   k_work_schedule                          <= FUN_00073418 @ 0x00073418
 * address symbols (name @ address):
 *   g_audio_module_spinlock                  @ 0x200068d0
 */
/* Reconstructed FUN_00073418 @ 0x73418  (parity: 300/300 trials, PROVEN) */

extern int k_work_schedule_for_queue(unsigned long, volatile unsigned long*, unsigned long, unsigned long);
void k_work_schedule(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    k_work_schedule_for_queue(0x200068d0UL, param_1, param_3, param_4);
}
