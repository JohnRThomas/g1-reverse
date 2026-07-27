/* readable reconstruction; identity: FUN_00084b14 @ 0x00084b14
 * public-name: pinctrl_apply_state
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   pinctrl_lookup_state                     <= FUN_00083eb8 @ 0x00083eb8
 *   dppi_apply_channel_config_table          <= FUN_00083ede @ 0x00083ede
 *   pinctrl_apply_state                      <= FUN_00084b14 @ 0x00084b14
 */
/* Reconstructed FUN_00084b14 @ 0x84b14  (parity: 300/300 trials, PROVEN) */

extern int pinctrl_lookup_state(unsigned int *, unsigned int *, unsigned int **, unsigned int, unsigned int *);
extern int dppi_apply_channel_config_table(const unsigned long*, unsigned int, unsigned int);

void pinctrl_apply_state(unsigned int *param_1, unsigned int *param_2, unsigned int param_3, unsigned int param_4)
{
  int iVar1;
  unsigned int *local_c;

  local_c = param_2;
  iVar1 = pinctrl_lookup_state(param_1,param_2,&local_c,param_4,param_1);
  if (-1 < iVar1) {
    dppi_apply_channel_config_table(*local_c,*(unsigned char *)(local_c + 1),*param_1);
  }
  return;
}
