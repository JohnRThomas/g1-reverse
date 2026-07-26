/* readable reconstruction; identity: FUN_00018978 @ 0x00018978
 * public-name: discovery_service_not_found_cb_ancs
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gatt_discover                            <= FUN_000187e8 @ 0x000187e8
 *   discovery_service_not_found_cb_ancs      <= FUN_00018978 @ 0x00018978
 *   atomic_and                               <= FUN_0007c08e @ 0x0007c08e
 * address symbols (name @ address):
 *   rodata_9a7f2                             @ 0x0009a7f2   [INLINED -- G6 literal batch]
 *   g_gatt_discovery_flags                   @ 0x20006ab4
 */
/* Reconstructed FUN_00018978 @ 0x18978  (parity: 300/300 trials, PROVEN) */

extern void log_message(unsigned int);
extern void atomic_and(void *, unsigned int);
extern void gatt_discover(unsigned int, unsigned int);

void discovery_service_not_found_cb_ancs(unsigned int param_1)
{
  log_message(0x0009a7f2UL);
  atomic_and((void*)0x20006ab4UL,0xfffffffeUL);
  gatt_discover(param_1,1);
  return;
}
