/* readable reconstruction; identity: FUN_00086588 @ 0x00086588
 * public-name: notify_queue_locked
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_sched_wake                             <= FUN_00074a54 @ 0x00074a54
 *   notify_queue_locked                      <= FUN_00086588 @ 0x00086588
 */
/* Reconstructed FUN_00086588 @ 0x86588  (parity: 300/300 trials, PROVEN) */

extern int z_sched_wake(int *, unsigned int, unsigned int, unsigned int);

void notify_queue_locked(unsigned char *param_1, unsigned int unused_r1,
                  unsigned int unused_r2, unsigned int r3) {
  (void)unused_r1;
  (void)unused_r2;
  if (param_1 != 0) {
    (void)z_sched_wake((int *)(param_1 + 0xe0), 0, 0, r3);
  }
}
