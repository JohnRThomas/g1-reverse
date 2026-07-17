/* readable reconstruction; identity: FUN_0002bd4c @ 0x0002bd4c
 * public-name: imu_set_enabled
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   trigger_screen_state_change              <= FUN_0002bc2c @ 0x0002bc2c
 *   update_imu_trigger_status                <= FUN_0002bcbc @ 0x0002bcbc
 *   imu_set_enabled                          <= FUN_0002bd4c @ 0x0002bd4c
 * address symbols (name @ address):
 *   rodata_a24dc                             @ 0x000a24dc
 *   rodata_a24e4                             @ 0x000a24e4
 */
/* Reconstructed FUN_0002bd4c @ 0x2bd4c  (parity: 300/300 trials, PROVEN) */

extern int update_imu_trigger_status(unsigned int a, unsigned int b, unsigned int c, unsigned int d);
extern int trigger_screen_state_change(unsigned int a, unsigned int b, unsigned int c);

unsigned int imu_set_enabled(unsigned int param_1, unsigned int param_2, int param_3, unsigned int param_4)
{
  unsigned int uVar1;
  if (param_3 != 0) {
    update_imu_trigger_status(param_1, param_2, 1, param_4);
    uVar1 = 0xa24e4;
  } else {
    update_imu_trigger_status(param_1, param_2, 0, param_4);
    uVar1 = 0xa24dc;
  }
  trigger_screen_state_change(uVar1, param_2, param_3 != 0);
  return 0;
}
