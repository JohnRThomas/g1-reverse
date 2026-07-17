/* readable reconstruction; identity: FUN_0000ef12 @ 0x0000ef12
 * public-name: strlen
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   strlen                                   <= FUN_0000ef12 @ 0x0000ef12
 */
/* Reconstructed FUN_0000ef12 @ 0xef12  (parity: 300/300 trials, PROVEN) */

unsigned int strlen(char *param_1) {
  char *p = param_1;
  while (*p != 0) p++;
  return (unsigned int)((p + 1) - 1 - param_1);
}
