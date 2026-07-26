/* readable reconstruction; identity: FUN_000165b4 @ 0x000165b4
 * public-name: uarte_nrfx_irq_rx_ready
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   uarte_nrfx_irq_rx_ready                  <= FUN_000165b4 @ 0x000165b4
 * address symbols (name @ address):
 *   g_dashboard_startup_mode_info_defaults   @ 0x2007fc00
 */
/* Reconstructed FUN_000165b4 @ 0x165b4  (parity: 300/300 trials, PROVEN) */

int uarte_nrfx_irq_rx_ready(void) {
  int a = *(volatile int*)(0x2007fc00UL + 0x64);
  /* iteration 37: 0x165b8 `ldr r3,[pc,#12]` loads the literal-pool CONSTANT
   * 0x12345678 (the retained-block validity magic) into r3; 0x165ba then does
   * `subs r0,r0,r3`.  It is NOT a memory read.  Dereferencing it made a cold
   * boot look like a VALID retained block, so init_dashboard_info skipped the
   * branch that seeds the RTC record with 0x65920080 (2024-01-01). */
  int b = 0x12345678;
  int r = a - b;
  if (r != 0) r = -1;
  return r;
}
