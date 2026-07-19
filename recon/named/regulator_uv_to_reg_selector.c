/* readable reconstruction; identity: FUN_00062070 @ 0x00062070
 * public-name: regulator_uv_to_reg_selector
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   regulator_uv_to_reg_selector             <= FUN_00062070 @ 0x00062070
 * address symbols (name @ address):
 *   rodata_f4240                             @ 0x000f4240
 */
/* Reconstructed FUN_00062070 @ 0x62070  (parity: 300/300 trials, PROVEN) */

unsigned int regulator_uv_to_reg_selector(int param_1, int param_2, unsigned short *param_3)
{
  unsigned int uVar1 = 0x186a0;
  unsigned int uVar3;

  if ((param_2 <= 0xf423f) || (param_1 > 0x325aa0)) {
    return 0xffffffea;
  }
  if (param_1 <= 0xf423f) {
    *param_3 = 0;
    return 0xffffffde;
  }
  if (param_2 <= 0x325aa0) {
    uVar3 = ((unsigned int)param_1 - 0xdbba1U) / uVar1;
    *param_3 = (unsigned short)uVar3;
    if ((uVar1 * uVar3 + 0xf4240) <= (unsigned int)param_2) {
      return 0;
    }
    return 0xffffffea;
  }
  *param_3 = 0x17;
  return 0xffffffde;
}
