/* readable reconstruction; identity: FUN_000848b0 @ 0x000848b0
 * public-name: post_event_tag5
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   post_event_tag5                          <= FUN_000848b0 @ 0x000848b0
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 */
/* Reconstructed FUN_000848b0 @ 0x848b0  (parity: 300/300 trials, PROVEN) */

extern void memset_bytes(void *a, int b, int c);
extern void FUN_00084840(int a, void *b);
void post_event_tag5(int param_1)
{
  unsigned char local_1c[20];
  memset_bytes(local_1c, 0, 0x14);
  local_1c[0] = 5;
  FUN_00084840(param_1, local_1c);
}
