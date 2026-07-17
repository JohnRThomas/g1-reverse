/* readable reconstruction; identity: FUN_00072fdc @ 0x00072fdc
 * public-name: FUN_00072fdc
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   k_work_submit_to_queue                   <= FUN_000865fc @ 0x000865fc
 * address symbols (name @ address):
 *   g_audio_module_spinlock                  @ 0x200068d0
 */
/* Reconstructed FUN_00072fdc @ 0x72fdc  (parity: 300/300 trials, PROVEN) */

extern void k_work_submit_to_queue(unsigned int, unsigned int);
void FUN_00072fdc(unsigned int param_1)
{
    k_work_submit_to_queue(0x200068d0UL, param_1);
}
