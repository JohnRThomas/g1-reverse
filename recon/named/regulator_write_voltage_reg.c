/* readable reconstruction; identity: FUN_000842cc @ 0x000842cc
 * public-name: regulator_write_voltage_reg
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   regulator_uv_to_reg_selector             <= FUN_00062070 @ 0x00062070
 *   dev_write_reg3                           <= FUN_00083dc8 @ 0x00083dc8
 *   regulator_write_voltage_reg              <= FUN_000842cc @ 0x000842cc
 */
/* Reconstructed FUN_000842cc @ 0x842cc  (parity: 300/300 trials, PROVEN) */

extern int regulator_uv_to_reg_selector(unsigned int, unsigned int, void *, unsigned int, int);
extern int dev_write_reg3(unsigned int, unsigned int, unsigned int, unsigned int);

void regulator_write_voltage_reg(int param_1, int param_2, unsigned int param_3, unsigned int param_4)
{
  int iVar1;
  unsigned int uStack_14;
  unsigned int uStack_10;
  uStack_14 = param_2;
  uStack_10 = param_3;
  iVar1 = regulator_uv_to_reg_selector(param_3, param_4, (unsigned char *)&uStack_14 + 2, param_4, param_1);
  if (iVar1 != -0x16) {
    dev_write_reg3(*(unsigned int *)(param_1 + 0x1c), 8, (param_2 + 0xc) & 0xff, *((unsigned char *)&uStack_14 + 2));
  }
}
