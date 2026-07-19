/* readable reconstruction; identity: FUN_00018300 @ 0x00018300
 * public-name: ancs_conn_event_signal_and_mode
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ancs_conn_event_signal_and_mode          <= FUN_00018300 @ 0x00018300
 *   k_sem_give                               <= FUN_00072880 @ 0x00072880
 * address symbols (name @ address):
 *   rodata_9a436                             @ 0x0009a436
 *   g_ancs_active_conn                       @ 0x20006ab8
 */
/* Reconstructed FUN_00018300 @ 0x18300  (parity: 300/300 trials, PROVEN) */

extern void log_message(int);
extern void k_sem_give(int);
extern void change_work_mode_to(int);
void ancs_conn_event_signal_and_mode(int param_1, unsigned int param_2)
{
    log_message(0x0009a436);
    if (99 < param_2) {
        k_sem_give(*(volatile int*)0x20006ab8UL + 0x230);
        if (param_2 == 0x1f2) {
            change_work_mode_to(1);
            return;
        }
    }
}
