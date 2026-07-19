/* readable reconstruction; identity: FUN_000531d8 @ 0x000531d8
 * public-name: reschedule_on_sys_work_q
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   reschedule_on_sys_work_q                 <= FUN_000531d8 @ 0x000531d8
 *   k_work_reschedule_for_queue              <= FUN_00073424 @ 0x00073424
 * address symbols (name @ address):
 *   g_sys_work_q                             @ 0x20005d38
 */
/* Reconstructed FUN_000531d8 @ 0x531d8  (parity: 300/300 trials, PROVEN) */

extern unsigned int k_work_reschedule_for_queue(unsigned int a, void *b);
unsigned int reschedule_on_sys_work_q(void *param_1)
{
    return k_work_reschedule_for_queue(0x20005d38UL, param_1);
}
