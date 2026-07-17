/* readable reconstruction; identity: FUN_00033c4c @ 0x00033c4c
 * public-name: get_message_entry
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_message_entry                        <= FUN_00033c4c @ 0x00033c4c
 * address symbols (name @ address):
 *   g_message_pool                           @ 0x20007dac
 */
/* Reconstructed FUN_00033c4c @ 0x33c4c  (parity: 300/300 trials, PROVEN) */

int get_message_entry(int param_1)
{
  return param_1 * 0x1b4 + 0x20007dac;
}
