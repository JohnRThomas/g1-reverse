/* readable reconstruction; identity: FUN_00037060 @ 0x00037060
 * public-name: sync_dashboard_default_language
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   set_dashboard_startup_default_language   <= FUN_0001672c @ 0x0001672c
 *   sync_dashboard_default_language          <= FUN_00037060 @ 0x00037060
 * address symbols (name @ address):
 *   g_dashboard_widget_state                 @ 0x20004950
 *   g_widget0_index_raw                      @ 0x2001b816
 */
/* Reconstructed FUN_00037060 @ 0x37060  (parity: 300/300 trials, PROVEN) */

extern void set_dashboard_startup_default_language(unsigned char);

unsigned long sync_dashboard_default_language(void) {
  unsigned int base = 0x20004950UL;
  unsigned char value = *(volatile unsigned char *)0x2001b816UL;
  *(volatile unsigned char *)(base + 1) = value;
  set_dashboard_startup_default_language(value);
  return *(volatile unsigned char *)(base + 1);
}
