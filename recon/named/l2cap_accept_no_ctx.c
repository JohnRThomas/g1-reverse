/* readable reconstruction; identity: FUN_00057438 @ 0x00057438
 * public-name: l2cap_accept_no_ctx
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   l2cap_accept_no_ctx                      <= FUN_00057438 @ 0x00057438
 * address symbols (name @ address):
 *   rodata_88160                             @ 0x00088160
 *   rodata_f3eea                             @ 0x000f3eea
 */
/* Reconstructed FUN_00057438 @ 0x57438  (parity: 300/300 trials, PROVEN) */

extern void FUN_00081746(unsigned int a0, unsigned int a1, void *a2);

unsigned int l2cap_accept_no_ctx(unsigned int param_1)
{
  unsigned int local[3];
  local[0] = 3;
  local[1] = 0x000f3eea;
  local[2] = param_1;
  FUN_00081746(0x00088160, 0x1840, local);
  return 0xfffffff4;
}
