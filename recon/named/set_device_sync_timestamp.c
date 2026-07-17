/* readable reconstruction; identity: FUN_0007d230 @ 0x0007d230
 * public-name: set_device_sync_timestamp
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   set_device_sync_timestamp                <= FUN_0007d230 @ 0x0007d230
 */
/* Reconstructed FUN_0007d230 @ 0x7d230  (parity: 300/300 trials, PROVEN) */

extern unsigned int get_device_info(void);
unsigned int set_device_sync_timestamp(unsigned int param_1) {
  unsigned int r = get_device_info();
  *(unsigned int*)(r + 0xd0) = param_1;
  return param_1;
}
