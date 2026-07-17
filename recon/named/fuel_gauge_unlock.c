/* readable reconstruction; identity: FUN_000330d8 @ 0x000330d8
 * public-name: fuel_gauge_unlock
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   fuel_gauge_unlock                        <= FUN_000330d8 @ 0x000330d8
 *   unlock_device_mutex                      <= FUN_0007c8c4 @ 0x0007c8c4
 * address symbols (name @ address):
 *   g_fuel_gauge_dev                         @ 0x20002424
 */
/* Reconstructed FUN_000330d8 @ 0x330d8  (parity: 300/300 trials, PROVEN) */

extern void unlock_device_mutex(int);

unsigned int fuel_gauge_unlock(void) {
  unsigned int value = *(volatile unsigned int *)0x20002424UL;
  if (value != 0) {
    unlock_device_mutex((int)value);
  }
  return 0;
}
