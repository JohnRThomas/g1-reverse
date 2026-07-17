/* readable reconstruction; identity: FUN_00018ab0 @ 0x00018ab0
 * public-name: ancs_cancel_timers
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ancs_cancel_timers                       <= FUN_00018ab0 @ 0x00018ab0
 *   atomic_and                               <= FUN_0007c08e @ 0x0007c08e
 * address symbols (name @ address):
 *   g_gatt_discovery_flags                   @ 0x20006ab4
 */
/* Reconstructed FUN_00018ab0 @ 0x18ab0  (parity: 300/300 trials, PROVEN) */

extern void atomic_and(unsigned int a0, unsigned int a1);

void ancs_cancel_timers(void)
{
  atomic_and(0x20006ab4, 0xfffffffe);
  atomic_and(0x20006ab4, 0xfffffffd);
  atomic_and(0x20006ab4, 0xfffffffb);
}
