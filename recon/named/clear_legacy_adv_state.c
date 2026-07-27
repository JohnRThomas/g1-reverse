/* readable reconstruction; identity: FUN_0005571c @ 0x0005571c
 * public-name: clear_legacy_adv_state
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   clear_legacy_adv_state                   <= FUN_0005571c @ 0x0005571c
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   g_bt_le_legacy_adv                       @ 0x20002018
 */
/* Reconstructed FUN_0005571c @ 0x5571c  (parity: 300/300 trials, PROVEN) */

extern void memset_bytes(void*, int, int);
void clear_legacy_adv_state(void)
{
  memset_bytes(0x20002018UL, 0, 0x50);
}
