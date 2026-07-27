struct k_mutex;
/* readable reconstruction; identity: FUN_00019b48 @ 0x00019b48
 * public-name: ble_work_queue_unlock
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ble_work_queue_unlock                    <= FUN_00019b48 @ 0x00019b48
 *   k_mutex_unlock                           <= FUN_00072558 @ 0x00072558
 * address symbols (name @ address):
 *   g_ble_work_queue                         @ 0x20007574
 */
/* Reconstructed FUN_00019b48 @ 0x19b48  (parity: 300/300 trials, PROVEN) */

extern int k_mutex_unlock(struct k_mutex *);
void ble_work_queue_unlock(void) {
    k_mutex_unlock(0x20007574UL);
}
