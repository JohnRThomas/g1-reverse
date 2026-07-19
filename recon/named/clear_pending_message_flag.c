/* readable reconstruction; identity: FUN_0002c214 @ 0x0002c214
 * public-name: clear_pending_message_flag
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   clear_pending_message_flag               <= FUN_0002c214 @ 0x0002c214
 * address symbols (name @ address):
 *   g_pending_message_flag                   @ 0x20018d9e
 */
/* Reconstructed FUN_0002c214 @ 0x2c214  (parity: 300/300 trials, PROVEN) */

void clear_pending_message_flag(void)
{
  if (*(volatile unsigned char *)0x20018d9eUL != 0) {
    *(volatile unsigned char *)0x20018d9eUL = 0;
  }
}
