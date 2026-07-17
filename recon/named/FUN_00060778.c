/* readable reconstruction; identity: FUN_00060778 @ 0x00060778
 * public-name: FUN_00060778
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed FUN_00060778 @ 0x60778  (parity: 300/300 trials, PROVEN) */

unsigned int FUN_00060778(unsigned int param_1)
{
  unsigned int b = param_1 & 0xffu;
  return 0x2000b098UL + (b << 5);
}
