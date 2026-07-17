/* readable reconstruction; identity: FUN_00073418 @ 0x00073418
 * public-name: FUN_00073418
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   k_work_schedule_for_queue                <= FUN_0007332c @ 0x0007332c
 * address symbols (name @ address):
 *   g_audio_module_spinlock                  @ 0x200068d0
 */
/* Reconstructed FUN_00073418 @ 0x73418  (parity: 300/300 trials, PROVEN) */

extern void k_work_schedule_for_queue(unsigned int, unsigned int, unsigned int, unsigned int);
void FUN_00073418(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    k_work_schedule_for_queue(0x200068d0UL, param_1, param_3, param_4);
}
