/* readable reconstruction; identity: FUN_0005cbe0 @ 0x0005cbe0
 * public-name: smp_dhkey_ready_no_context
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   smp_dhkey_ready_no_context               <= FUN_0005cbe0 @ 0x0005cbe0
 *   smp_log_message                          <= FUN_00083074 @ 0x00083074
 * address symbols (name @ address):
 *   rodata_88180                             @ 0x00088180
 *   rodata_f4e22                             @ 0x000f4e22
 */
/* Reconstructed FUN_0005cbe0 @ 0x5cbe0  (parity: 300/300 trials, PROVEN) */

extern void smp_log_message(unsigned int a0, unsigned int a1, void *a2);

unsigned int smp_dhkey_ready_no_context(unsigned int param_1)
{
  unsigned int local[3];
  local[0] = 3;
  local[1] = 0x000f4e22;
  local[2] = param_1;
  smp_log_message(0x00088180, 0x1840, local);
  return 0xfffffff4;
}
