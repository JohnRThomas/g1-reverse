/* readable reconstruction; identity: FUN_0002e8fc @ 0x0002e8fc
 * public-name: opt3007_init_ctx_setup
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   opt3007_init_ctx_setup                   <= FUN_0002e8fc @ 0x0002e8fc
 * address symbols (name @ address):
 *   ADDR_opt3001_read_lux_raw_THUMB          @ 0x0002e649
 *   ADDR_opt3007_chip_init_THUMB             @ 0x0002e67d
 */
/* Reconstructed FUN_0002e8fc @ 0x2e8fc  (parity: 300/300 trials, PROVEN) */

void opt3007_init_ctx_setup(unsigned int *param_1) {
  param_1[7] = (unsigned int)param_1 - 0x430;
  param_1[0] = 0x0002e67dUL;
  param_1[3] = 0x0002e649UL;
}
