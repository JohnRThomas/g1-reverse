/* readable reconstruction; identity: FUN_00084300 @ 0x00084300
 * public-name: regulator_set_voltage_range
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   regulator_uv_to_reg_selector             <= FUN_00062070 @ 0x00062070
 *   dev_write_reg3                           <= FUN_00083dc8 @ 0x00083dc8
 *   dev_reg_modify_bits                      <= FUN_00083e0e @ 0x00083e0e
 *   regulator_set_voltage_range              <= FUN_00084300 @ 0x00084300
 */
/* Reconstructed FUN_00084300 @ 0x84300  (parity: 300/300 trials, PROVEN) */

extern int regulator_uv_to_reg_selector(unsigned int, unsigned int, void*);
extern int dev_write_reg3(unsigned int, int, int, int);
extern void dev_reg_modify_bits(unsigned int, int, int, unsigned int, unsigned int);

void regulator_set_voltage_range(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  unsigned char stk[0x14];
  int iVar1;
  unsigned int uVar2;

  iVar1 = regulator_uv_to_reg_selector(param_3, param_4, stk+0xe);
  if (iVar1 != -0x16) {
    iVar1 = dev_write_reg3(*(unsigned int*)(param_1+0x1c), 4, ((param_2+4)*2) & 0xfe, stk[0xe]);
    if (iVar1 >= 0) {
      uVar2 = (1u << (param_2 & 0xff)) & 0xff;
      dev_reg_modify_bits(*(unsigned int*)(param_1+0x1c), 4, 0xf, uVar2, uVar2);
    }
  }
  return;
}
