/* readable reconstruction; identity: FUN_00085200 @ 0x00085200
 * public-name: audio_i2s_stream0_trigger_start
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   audio_i2s_stream0_trigger_start          <= FUN_00085200 @ 0x00085200
 */
/* Reconstructed FUN_00085200 @ 0x85200.
 * Complete six-byte tail-call wrapper; 0x85206 starts the next function. */
extern int FUN_00066524(int, int, int, int);
int audio_i2s_stream0_trigger_start(int param_1, int param_2, int param_3) {
  return FUN_00066524(param_1, param_2, param_3, 2);
}
