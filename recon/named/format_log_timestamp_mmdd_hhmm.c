/* readable reconstruction; identity: FUN_0007ca80 @ 0x0007ca80
 * public-name: format_log_timestamp_mmdd_hhmm
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   format_log_timestamp_mmdd_hhmm           <= FUN_0007ca80 @ 0x0007ca80
 */
/* Reconstructed FUN_0007ca80 @ 0x7ca80  (parity: 300/300 trials, PROVEN) */

int format_log_timestamp_mmdd_hhmm(unsigned char *param_1)
{
  param_1[0] = param_1[4];
  param_1[1] = param_1[5];
  param_1[2] = 0x2d;
  param_1[3] = param_1[6];
  param_1[4] = param_1[7];
  param_1[5] = 0x20;
  param_1[6] = param_1[9];
  param_1[7] = param_1[10];
  param_1[8] = 0x3a;
  param_1[9] = param_1[11];
  param_1[10] = param_1[12];
  param_1[11] = 0;
  return 0xc;
}
